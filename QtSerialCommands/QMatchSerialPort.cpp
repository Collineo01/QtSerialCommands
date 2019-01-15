/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/

#include "QMatchSerialPort.h"
#include "SerialPortSettings.h"

#include <QVariant>
#include <QTime>
#include <QCoreApplication>
#include <QTimer>
#include <QMutex>
#include <QThread>
#include <QDebug>

QMatchSerialPort::QMatchSerialPort(const SerialMessageFactory & serialMessagesFactory, bool isAutoReconnecting) : // TODO : SerialSettings should belong to QAsyncSerialPort (pass to ctor).
	QAsyncSerialPort(),
	m_serialMessages{ serialMessagesFactory.createSerialMessages() },
	m_gotDisconnected{ false },
	m_hasChangedSettings{ false },
	m_isAutoReconnecting{ isAutoReconnecting }
{
	m_commandTimer.setSingleShot(true);

	qRegisterMetaType<SerialCommand>("SerialCommand");


	connect(&m_serialBuffer, &QSerialBuffer::commandIsReadyToSend, this, &QMatchSerialPort::handleCommandReadyToSend);
	connect(this, &QAsyncSerialPort::dataRead, this, &QMatchSerialPort::handleResponse, Qt::QueuedConnection);
	connect(&m_commandTimer, &QTimer::timeout, this, &QMatchSerialPort::handlePullCommandTimeout, Qt::QueuedConnection);
	connect(this, &QMatchSerialPort::smartMatchingModeChanged, this, &QMatchSerialPort::handleSmartMatchingModeChange, Qt::QueuedConnection);
	connect(this, &QMatchSerialPort::sendCommandRequested, this, &QMatchSerialPort::handleSendCommandRequest, Qt::QueuedConnection);
}

QMatchSerialPort::QMatchSerialPort() :
	QMatchSerialPort(DummySerialMessageFactory())
{
}

QMatchSerialPort::~QMatchSerialPort()
{

}

void QMatchSerialPort::sendCommand(SerialCommand & command, QList<SerialCommandArg> args)
{
	// TODO : throw exception if not connected instead of connecting.
	command.setArgs(args);
	m_serialBuffer.writeCommand(command);
}

QByteArray QMatchSerialPort::sendBlockingCommandSync(SerialCommand & command, QList<SerialCommandArg> args)
{
	command.setArgs(args);

	m_syncBlockingCommandSent = &command;

	emit sendCommandRequested(command);

	QTimer t(this);
	t.setSingleShot(true);
	t.start(m_timeout);

	while (m_syncBlockingCommandSent == &command && t.isActive()) {
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
	m_serialBuffer.writeCommand(command);
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
	if (!m_isBypassingSmartMatchingMode)
	{
		m_serialBuffer.writeResponse(data);

		QThread responseAnalyzingThread;
		QSerialResponseAnalyzer responseAnalyzer(m_serialBuffer, m_serialMessages);
		responseAnalyzer.moveToThread(&responseAnalyzingThread);
		connect(&responseAnalyzer, &QSerialResponseAnalyzer::foundMatchingResponse, this, &QMatchSerialPort::handleFoundMatchingResponse);
		connect(&responseAnalyzer, &QSerialResponseAnalyzer::commandIsReadyToSend, this, &QMatchSerialPort::handleCommandReadyToSend);
		connect(&responseAnalyzer, &QSerialResponseAnalyzer::foundMessage, this, &QMatchSerialPort::messageReceived);
		connect(&responseAnalyzingThread, &QThread::started, &responseAnalyzer, &QSerialResponseAnalyzer::analyzeResponses);
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

void QMatchSerialPort::handleSmartMatchingModeChange(bool isBypassing)
{
	if (isBypassing) {
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

void QMatchSerialPort::handleCommandReadyToSend(const SerialCommand & command)
{
	if (sendMessage(command.commandToSend())) {
		if (!m_isBypassingSmartMatchingMode)
		{
			QThread commandManagerThread;
			QSerialCommandManager commandManager(m_serialBuffer);
			commandManager.moveToThread(&commandManagerThread);
			connect(&commandManager, &QSerialCommandManager::commandIsReadyToSend, this, &QMatchSerialPort::handleCommandReadyToSend);
			connect(&commandManagerThread, &QThread::finished, &commandManager, &QObject::deleteLater);
			connect(&commandManagerThread, &QThread::finished, &commandManagerThread, &QThread::deleteLater);
			commandManagerThread.start();
			m_commandTimer.start(m_timeout);
		}
	}
}

void QMatchSerialPort::handleFoundMatchingResponse(const QByteArray & response, const SerialCommand & command)
{
	if (command.getOperationMode().blockingMode() == SerialOperationMode::BlockingMode::Blocking)
	{
		m_commandTimer.stop();
	}
	if (*m_syncBlockingCommandSent == command)
	{
		m_syncBlockingResponse = response;
		m_syncBlockingCommandSent = nullptr;
	}
	else
	{
		emit matchingResponseReceived(response, command);
	}
}

void QMatchSerialPort::changeSerialPortSettings(SerialPortSettings * portSettings, bool blocking)
{
	if (isOpen())
	{
		closePort();
		openPort(portSettings);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Set
///////////////////////////////////////////////////////////////////////////////////////////////

void QMatchSerialPort::setBypassingSmartMatchingMode(bool isBypassing) {
	m_isBypassingSmartMatchingMode = isBypassing;
	emit smartMatchingModeChanged(isBypassing);
}

