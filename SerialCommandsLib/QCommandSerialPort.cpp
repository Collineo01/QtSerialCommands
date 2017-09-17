/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/

#include "QCommandSerialPort.h"
#include <QVariant>
#include <QTime>
#include <QCoreApplication>
#include <QTimer>
#include <QMutex>
#include <QDebug>

QCommandSerialPort::QCommandSerialPort(int sendBufferSize, int responsesBufferSize)
	: QAsyncSerialPort(),
	mSendBufferSize{ sendBufferSize },
	mResponsesSize{ responsesBufferSize },
	mCurrentOperationMode{ SerialOperationMode::BlockingMode::Blocking, SerialOperationMode::FluxMode::Pull },
	mDevelopmentMode{ false },
	mBlockingCommandSent{ nullptr },
	m_GotDisconnected{ false },
	m_HasChangedSettings{ false }
{
	mCommandTimer.setSingleShot(true);

	qRegisterMetaType<SerialCommand>("SerialCommand");

	connect(this, &QAsyncSerialPort::dataRead, this, &QCommandSerialPort::handleResponse, Qt::QueuedConnection);
	connect(this, &QAsyncSerialPort::messageSent, this, &QCommandSerialPort::manageMessageSent, Qt::QueuedConnection);
	connect(&mCommandTimer, &QTimer::timeout, this, &QCommandSerialPort::handlePullCommandTimeout, Qt::QueuedConnection);
	connect(this, &QCommandSerialPort::developmentModeSwitched, this, &QCommandSerialPort::handleDevelopmentMode, Qt::QueuedConnection);
	connect(this, &QCommandSerialPort::disconnectRequest, this, &QCommandSerialPort::handleDisconnectRequest, Qt::QueuedConnection);
	connect(this, &QCommandSerialPort::changeSerialSettingsRequest, this, &QCommandSerialPort::handleChangeSerialSettingsRequest, Qt::QueuedConnection);
	connect(this, &QCommandSerialPort::clearBuffersRequest, this, &QCommandSerialPort::handleClearBuffersRequest, Qt::QueuedConnection);
	connect(this, &QCommandSerialPort::removeLastCommandSentRequest, this, &QCommandSerialPort::handleRemoveLastCommandSent, Qt::QueuedConnection);
	connect(this, &QCommandSerialPort::removeFirstCommandToSendRequest, this, &QCommandSerialPort::handleRemoveFirstCommandToSend, Qt::QueuedConnection);
	connect(this, &QCommandSerialPort::sendCommandRequest, this, &QCommandSerialPort::handleSendCommandRequest, Qt::QueuedConnection);
}

QCommandSerialPort::~QCommandSerialPort()
{

}


///////////////////////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////////////////////

void QCommandSerialPort::handleSendCommandRequest(SerialCommand command)
{
	writeToBuffer(command);
}

void QCommandSerialPort::sendFromBuffer() 
{
	if (!mCommandsToSend.isEmpty())
	{
		SerialCommand &command = mCommandsToSend[0];
		mCurrentOperationMode = command.operationMode();

		if (sendMessage(command.commandToSend())) {
			m_LastCommandSent = mCommandsToSend[0];
		}
	}
}

/*! Les commandes doivent impérativement être envoyées à partir d'ici pour que la gestion s'effectue correctement.
*/
void QCommandSerialPort::writeToBuffer(SerialCommand const & command)
{
	QMutex mutex;
	mutex.lock();
	if (!(command.operationMode().blockingMode() == SerialOperationMode::BlockingMode::NonBlockingUniqueResponse && (mCommandsToSend.contains(command) || mCommandsSent.contains(command)))) 
	{
		mCommandsToSend.append(command);

		if (mCommandsToSend.size() == 1 && (mCommandsSent.isEmpty() || mCommandsSent.last().operationMode().blockingMode() != SerialOperationMode::BlockingMode::Blocking)) {
			sendFromBuffer();
		}
		if (mCommandsToSend.size() >= mSendBufferSize) {
			emit sendBufferTooLarge();  // intercept signal
		}
	}
	mutex.unlock();
}

QByteArray QCommandSerialPort::sendBlockingCommand(SerialCommand command, QList<QVariant> params)
{
	command.setParameters(params);

	mBlockingCommandSent = &command;

	emit sendCommandRequest(command);
	//writeToBuffer(command);
	
	QTimer t(this);
	t.setSingleShot(true);
	t.start(m_Timeout);

	//connect(&t, &QTimer::timeout, this, &QCommandSerialPort::handlePullCommandTimeout, Qt::QueuedConnection);

	while (mBlockingCommandSent == &command && t.isActive()) {
		QCoreApplication::processEvents();
	}

	if (t.isActive()) {
		t.stop();
		return mBlockingResponse;
	}

	qDebug() << "Response timeout for command : " + command.name() + " on port " + portName();

	return QByteArray();
}

QByteArray QCommandSerialPort::responseMatchingCommand(SerialCommand command)
{
	QByteArray correspondingResponse = command.getFirstMatch(mResponses);
	// if we found a response matching the command
	if (!correspondingResponse.isNull())
	{
		QMutex mutex;
		mutex.lock();
		mResponses.remove(mResponses.indexOf(correspondingResponse), correspondingResponse.length());
		mutex.unlock();
	}
	return correspondingResponse;
}

/*! À chaque réponse reçue, le tampon mResponses est analysé pour trouver toutes les réponses qui correspondent à l'une des commandes dans mCommandsSent.
*	Les tampons sont gérés en fonction du mode d'opération de chaque commande.
*
*/
void QCommandSerialPort::analyseAllResponses()
{
	QList<SerialCommand>::iterator commands = mCommandsSent.begin();
	while (commands != mCommandsSent.end() && !mCommandsSent.isEmpty())
	{
		SerialCommand command = *commands;
		QByteArray response = responseMatchingCommand(command);
		if (!response.isNull())
		{
			//qDebug() << "response : " << response;
			// Pull mode
			if (command.operationMode().fluxMode() == SerialOperationMode::FluxMode::Pull)
			{
				if (command.operationMode().blockingMode() == SerialOperationMode::BlockingMode::Blocking)
				{
					QMutex mutex;
					mutex.lock();
					commands = mCommandsSent.erase(commands);
					mutex.unlock();
					mCommandTimer.stop(); // the response is received, so we don't want to trigger a timeout
					sendFromBuffer(); // we waited for the response, now we can send the next command
				}
				else {
					QMutex mutex;
					mutex.lock();
					commands = mCommandsSent.erase(commands);
					mutex.unlock();
				}
				if (mBlockingCommandSent != nullptr && *mBlockingCommandSent == command)
				{
					mBlockingResponse = response;
					emit blockingResponseReceived();
					mBlockingCommandSent = nullptr;
				}
				else
				{
					emit responseMatchesCommand(response, command);
				}
				continue;
			}
			// Push mode
			else {
				while (!response.isNull()) 
				{
					emit responseMatchesCommand(response, command);
					response = responseMatchingCommand(command);
				}
			}
		}
		++commands;
	}
	// if the device is able to send messages on its own (not a command response), and there is something left in the buffer.
	if (!mDeviceMessages.isEmpty() && !mResponses.isEmpty()) {
		QByteArray messages = mResponses;
		QByteArray message = takeFirstResponse();
		while (!message.isNull() && mDeviceMessages.contains(message)) {
			emit messageReceived(message);
			removeFirstResponse(message);
			message = takeFirstResponse();
		}
	}
}

//bool QCommandSerialPort::retrySend(QString command) {
//	QMessageBox retry;
//	retry.setWindowTitle("No response received");
//	retry.setText(command + " command did not receive a proper response on time. Retry?");
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

void QCommandSerialPort::manageMessageSent() 
{
	if (!mDevelopmentMode && isOpen()) 
	{
		QList<SerialCommand>::iterator commands = mCommandsSent.begin();
		while (commands != mCommandsSent.end())
		{
			SerialCommand &command = *commands;
			// Push mode
			if (command.operationMode().fluxMode() == SerialOperationMode::FluxMode::Push) {
				if (command.stopsPushMode(mCommandsToSend[0])) {
					QMutex mutex;
					mutex.lock();
					commands = mCommandsSent.erase(commands);
					mutex.unlock();
					break;
				}
			}
			++commands;
		}
		if (mCurrentOperationMode.blockingMode() == SerialOperationMode::BlockingMode::NonBlockingNoResponse) {
			QMutex mutex;
			mutex.lock();
			mCommandsToSend.removeFirst();
			mutex.unlock();
			sendFromBuffer();
		}
		else if (mCurrentOperationMode.blockingMode() == SerialOperationMode::BlockingMode::NonBlockingOneToOneResponse || mCurrentOperationMode.blockingMode() == SerialOperationMode::BlockingMode::NonBlockingUniqueResponse) 
		{
			QMutex mutex;
			mutex.lock();
			mCommandsSent.append(mCommandsToSend.takeFirst());
			mutex.unlock();
			sendFromBuffer();
		}
		else {
			mCommandTimer.start(m_Timeout);
			QMutex mutex;
			mutex.lock();
			mCommandsSent.append(mCommandsToSend.takeFirst());
			mutex.unlock();
		}
	}
}

void QCommandSerialPort::handleResponse(QByteArray data) 
{
	if (!mDevelopmentMode) 
	{
		QMutex mutex;
		mutex.lock();
		mResponses.append(data);
		mutex.unlock();
		if (mResponses.size() >= mResponsesSize) {
			emit responsesBufferTooLarge(); // intercept signal
		}
		analyseAllResponses();
	}
}

void QCommandSerialPort::handlePullCommandTimeout() 
{
	removeLastCommandSent();
	emit commandTimeout(m_LastCommandSent, portName().right(1).toInt());
	qDebug() << "Command timed out (" + m_LastCommandSent.name() + ") for port " + portName() + ", error: " + errorString() << endl;
	//QString lastCommand(mCommandsSent.last().first.name() + " (" + mCommandsSent.last().first.command() + ")");
	//if (retrySend(lastCommand)) {
	//	writeToBuffer(mCommandsSent.takeLast());
	//}
	//else {
	//}
}

void QCommandSerialPort::handleDevelopmentMode(bool devMode) 
{
	if (devMode) {
		clearBuffers();
	}
}

void QCommandSerialPort::closeSerialPort() 
{
	if (isOpen())
	{
		emit disconnectRequest();

		QDebug debug = qDebug();
		debug << "Closing port " + portName();
		m_GotDisconnected = false;
		while (!m_GotDisconnected)
		{
			QCoreApplication::processEvents();
			debug << ".";
		}
	}
}

void QCommandSerialPort::changeSerialSettings(SerialSettings * portSettings) 
{
	if (isOpen()) 
	{
		emit changeSerialSettingsRequest(portSettings);

		QDebug debug = qDebug();
		debug << "Changing settings on " + portName();
		m_HasChangedSettings = false;
		while (!m_HasChangedSettings)
		{
			QCoreApplication::processEvents();
			debug << ".";
		}
	}
}

void QCommandSerialPort::removeLastCommandSent()
{
	emit removeLastCommandSentRequest();
}

void QCommandSerialPort::handleRemoveLastCommandSent()
{
	if (!mCommandsSent.isEmpty()) {
		QMutex mutex;
		mutex.lock();
		mCommandsSent.removeLast();
		mutex.unlock();
	}
}

void QCommandSerialPort::handleRemoveFirstCommandToSend()
{
	if (!mCommandsToSend.isEmpty()) {
		QMutex mutex;
		mutex.lock();
		mCommandsToSend.removeFirst();
		mutex.unlock();
	}
}

void QCommandSerialPort::clearBuffers()
{
	emit clearBuffersRequest();
}

void QCommandSerialPort::handleClearBuffersRequest()
{
	clearBuffersNow();
}

void QCommandSerialPort::clearBuffersNow()
{
	QMutex mutex;
	mutex.lock();
	mCommandsToSend.clear();
	mCommandsSent.clear();
	mResponses.clear();
	mCommandTimer.stop();
	mutex.unlock();
}

void QCommandSerialPort::handleDisconnectRequest() 
{
	clearBuffersNow();
	QAsyncSerialPort::closeSerialPort();

	m_GotDisconnected = true;
}

void QCommandSerialPort::handleChangeSerialSettingsRequest(SerialSettings * portSettings)
{
	handleDisconnectRequest();
	QAsyncSerialPort::openSerialPort(portSettings->mPortName, portSettings->mBaudRate, portSettings->mDataBits, portSettings->mParity, portSettings->mStopBits, portSettings->mFlowControl);

	m_HasChangedSettings = true;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Set
///////////////////////////////////////////////////////////////////////////////////////////////

void QCommandSerialPort::setDevelopmentMode(bool devMode) {
	mDevelopmentMode = devMode;
	emit developmentModeSwitched(devMode);
}

void QCommandSerialPort::setDeviceMessages(QStringList messages, QString terminator) { // The terminator will be essential to separate every messages we receive
	mDeviceMessages = messages;
	mTerminator = terminator;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Helper Methods
///////////////////////////////////////////////////////////////////////////////////////////////

QByteArray QCommandSerialPort::takeFirstResponse() {
	QRegularExpressionMatch match = QRegularExpression(".*" + mTerminator).match(mResponses);
	if (match.hasMatch()) {
		QString firstMatch = match.captured(0).remove(mTerminator);
		return firstMatch.toLatin1();
	}
	return QByteArray();
}

void QCommandSerialPort::removeFirstResponse(QByteArray data) {
	QMutex mutex;
	mutex.lock();
	mResponses.remove(mResponses.indexOf(data), data.length());
	mutex.unlock();
}

bool QCommandSerialPort::alreadySent(SerialCommand command) const 
{
	for (SerialCommand c : mCommandsToSend) {
		if (c == command) {
			return true;
		}
	}
	for (SerialCommand c : mCommandsSent) {
		if (c == command) {
			return true;
		}
	}
	return false;
}

