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
	m_responseProcessor{ m_serialBuffer, m_serialMessages },
	m_autoReconnect{ autoReconnect },
	m_gotDisconnected{ false },
	m_hasChangedSettings{ false },
	m_bypassSmartMatchingMode{ false },
	m_commandToSendAwait{ nullptr }
{
	m_commandTimer.setSingleShot(true);

	qRegisterMetaType<SerialCommand>("SerialCommand");


	connect(&m_serialBuffer, &QSerialBuffer::nextCommandReadyToSend, this, &QMatchSerialPort::handleNextCommandReadyToSend, Qt::QueuedConnection);
	connect(this, &QAsyncSerialPort::dataRead, this, &QMatchSerialPort::handleResponse, Qt::QueuedConnection);
	connect(&m_commandTimer, &QTimer::timeout, this, &QMatchSerialPort::handlePullCommandTimeout, Qt::QueuedConnection);
	connect(this, &QMatchSerialPort::smartMatchingModeChanged, this, &QMatchSerialPort::handleSmartMatchingModeChange, Qt::QueuedConnection);

	m_responseProcessor.moveToThread(&m_responseProcessingThread);
	connect(&m_responseProcessor, &QSerialResponseProcessor::foundMatchingResponse, this, &QMatchSerialPort::handleFoundMatchingResponse, Qt::QueuedConnection);
	connect(&m_responseProcessor, &QSerialResponseProcessor::nextCommandReadyToSend, this, &QMatchSerialPort::handleNextCommandReadyToSend, Qt::QueuedConnection);
	connect(&m_responseProcessor, &QSerialResponseProcessor::foundMessage, this, &QMatchSerialPort::messageReceived, Qt::QueuedConnection);
	connect(this, &QMatchSerialPort::processResponsesRequested, &m_responseProcessor, &QSerialResponseProcessor::processResponses, Qt::QueuedConnection);
	//connect(&m_responseProcessingThread, &QThread::finished, &m_responseProcessor, &QObject::deleteLater);
	//connect(&m_responseProcessingThread, &QThread::finished, &m_responseProcessingThread, &QThread::deleteLater);
	m_responseProcessingThread.start();
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
	m_responseProcessingThread.quit();
	m_responseProcessingThread.wait();
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////////////////////

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
	m_commandToSendAwait = &command;

	sendCommand(command);

	QTimer t(this);
	t.setSingleShot(true);
	t.start(m_timeout);

	while (m_commandToSendAwait == &command && t.isActive()) {
		QCoreApplication::processEvents();
	}

	if (t.isActive()) {
		t.stop();
		return m_awaitedResponse;
	}

	qDebug() << "Response timeout for getCommand : " + command.getName() + " on port " + portName();

	return QByteArray();
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
		emit processResponsesRequested();
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
	if (m_commandToSendAwait != nullptr && *m_commandToSendAwait == command)
	{
		m_awaitedResponse = response;
		m_commandToSendAwait = nullptr;
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

