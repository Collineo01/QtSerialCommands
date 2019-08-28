#include "QMatchSerialPort.h"
#include "SerialPortSettings.h"
#include "DefaultSerialPortSettings.h"

#include <QVariant>
#include <QTime>
#include <QCoreApplication>
#include <QTimer>
#include <QMutex>
#include <QThread>
#include <QDebug>

QMatchSerialPort::QMatchSerialPort(
	const SerialPortSettings& settings,
	const SerialMessageFactory& serialMessagesFactory, 
	bool autoReconnect
):
	QAsyncSerialPort(settings),
	m_serialMessages{ serialMessagesFactory.createSerialMessages() },
	m_autoReconnect{ autoReconnect },
	m_gotDisconnected{ false },
	m_hasChangedSettings{ false },
	m_bypassSmartMatchingMode{ false },
	m_commandToSend{ nullptr }
{
	m_commandTimer.setSingleShot(true);

	qRegisterMetaType<SerialCommand>("SerialCommand");


	connect(&m_serialBuffer, &QSerialBuffer::nextCommandIsReadyToSend, this, &QMatchSerialPort::handleNextCommandReadyToSend);
	connect(this, &QAsyncSerialPort::dataRead, this, &QMatchSerialPort::handleResponse, Qt::QueuedConnection);
	connect(&m_commandTimer, &QTimer::timeout, this, &QMatchSerialPort::handlePullCommandTimeout, Qt::QueuedConnection);
	connect(this, &QMatchSerialPort::smartMatchingModeChanged, this, &QMatchSerialPort::handleSmartMatchingModeChange, Qt::QueuedConnection);
	connect(this, &QMatchSerialPort::sendCommandRequested, this, &QMatchSerialPort::handleSendCommandRequest, Qt::QueuedConnection);
}

QMatchSerialPort::QMatchSerialPort(const SerialPortSettings & settings, bool autoReconnect):
	QMatchSerialPort(settings, DummySerialMessageFactory(), autoReconnect)
{
}

QMatchSerialPort::QMatchSerialPort(const SerialMessageFactory & serialMessagesFactory, bool autoReconnect):
	QMatchSerialPort(DefaultSerialPortSettings(), serialMessagesFactory, autoReconnect)
{
}

QMatchSerialPort::QMatchSerialPort(bool autoReconnect):
	QMatchSerialPort(DefaultSerialPortSettings(), DummySerialMessageFactory(), autoReconnect)
{
}

QMatchSerialPort::~QMatchSerialPort()
{

}

void QMatchSerialPort::sendCommand(SerialCommand command, QList<SerialCommandArg> args)
{
	setBypassSmartMatchingMode(false);

	// TODO : throw exception if not connected instead of connecting.
	if (!args.isEmpty())
	{
		command.setArgs(args);
	}
	m_serialBuffer.writeCommand(command);
}

QByteArray QMatchSerialPort::sendCommandAwait(SerialCommand command, QList<SerialCommandArg> args)
{
	setBypassSmartMatchingMode(false);

	if (!args.isEmpty())
	{
		command.setArgs(args);
	}

	m_commandToSend = &command;

	sendCommand(command);

	QTimer t(this);
	t.setSingleShot(true);
	t.start(m_timeout);

	while (m_commandToSend == &command && t.isActive()) {
		QCoreApplication::processEvents();
	}

	if (t.isActive()) {
		t.stop();
		return m_syncBlockingResponse;
	}

	qDebug() << "Response timeout for getCommand : " + command.getName() + " on port " + portName();

	return QByteArray();
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////////////////////

void QMatchSerialPort::handleSendCommandRequest(const SerialCommand & command)
{
	sendCommand(command);
}

//bool QMatchSerialPort::retrySend(QString getCommand) {
//	QMessageBox retry;
//	retry.setWindowTitle("No response received");
//	retry.setText(getCommand + " getCommand did not receive a proper response on time. Retry?");
//	retry.setIcon(QMessageBox::Question);
//	retry.setStandardButtons(QMessageBox::Yes);
//	retry.addButton(QMessageBox::No);
//	retry.setDefaultButton(QMessageBox::Yes);
//	if (retry.exec() == QMessageBox::Yes) {
//		return true;
//	}
//	return false;
//}


///////////////////////////////////////////////////////////////////////////////////////////////
// Slots
///////////////////////////////////////////////////////////////////////////////////////////////

void QMatchSerialPort::handleResponse(QByteArray data)
{
	if (!m_bypassSmartMatchingMode)
	{
		m_serialBuffer.writeResponse(data);

		QThread responseAnalyzingThread;
		QSerialResponseProcessor responseAnalyzer(m_serialBuffer, m_serialMessages);
		responseAnalyzer.moveToThread(&responseAnalyzingThread);
		connect(&responseAnalyzer, &QSerialResponseProcessor::foundMatchingResponse, this, &QMatchSerialPort::handleFoundMatchingResponse);
		connect(&responseAnalyzer, &QSerialResponseProcessor::commandIsReadyToSend, this, &QMatchSerialPort::handleNextCommandReadyToSend);
		connect(&responseAnalyzer, &QSerialResponseProcessor::foundMessage, this, &QMatchSerialPort::messageReceived);
		connect(&responseAnalyzingThread, &QThread::started, &responseAnalyzer, &QSerialResponseProcessor::processResponses);
		connect(&responseAnalyzingThread, &QThread::finished, &responseAnalyzer, &QObject::deleteLater);
		connect(&responseAnalyzingThread, &QThread::finished, &responseAnalyzingThread, &QThread::deleteLater);
		responseAnalyzingThread.start();
	}
}

void QMatchSerialPort::handlePullCommandTimeout()
{
	SerialCommand lastCommandSent = m_serialBuffer.takeLastCommandSent();
	emit commandTimedOut(lastCommandSent.getCommand(), lastCommandSent.getArgs(), portName().right(1).toInt());
	qDebug() << "Command timed out (" + lastCommandSent.getName() + ") for port " + portName() + ", error: " + errorString() << endl;
	//if (retrySend(lastCommand)) {
	//	writeCommand(m_sentCommandList.takeLast());
	//}
}

void QMatchSerialPort::handleSmartMatchingModeChange(bool bypass)
{
	if (bypass) {
		m_commandTimer.stop();
		m_serialBuffer.clearBuffersNow();
	}
}

void QMatchSerialPort::closePort()
{
	if (isOpen())
	{
		m_commandTimer.stop();
		m_serialBuffer.clearBuffersNow();
		QAsyncSerialPort::closePort();
	}
}

void QMatchSerialPort::handleNextCommandReadyToSend()
{
	if (sendData(m_serialBuffer.getNextCommandToSend().getSerialData())) 
	{
		m_serialBuffer.handleSentCommandToSend();
	}
	else
	{
		// TODO: throw exception
	}
}

void QMatchSerialPort::handleFoundMatchingResponse(const QByteArray & response, const SerialCommand & command)
{
	if (command.getOperationMode().blockingMode() == SerialOperationMode::BlockingMode::Blocking)
	{
		m_commandTimer.stop();
	}
	if (*m_commandToSend == command)
	{
		m_syncBlockingResponse = response;
		m_commandToSend = nullptr;
	}
	else
	{
		emit matchingResponseReceived(response, command);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Set
///////////////////////////////////////////////////////////////////////////////////////////////

void QMatchSerialPort::setBypassSmartMatchingMode(bool isBypassing) {
	m_bypassSmartMatchingMode = isBypassing;
	emit smartMatchingModeChanged(isBypassing);
}

