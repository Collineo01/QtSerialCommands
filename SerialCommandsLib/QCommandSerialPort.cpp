/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/

#include "QCommandSerialPort.h"
#include <QVariant>
#include <QTime>
#include <QEventLoop>
#include <QCoreApplication>
#include <QDebug>


QCommandSerialPort::QCommandSerialPort(int sendBufferSize, int responsesBufferSize)
	: QAsyncSerialPort(),
	mSendBufferSize{ sendBufferSize },
	mResponsesSize{ responsesBufferSize },
	mCurrentOperationMode{ SerialOperationMode::BlockingMode::Blocking, SerialOperationMode::FluxMode::Pull },
	mDevelopmentMode{ false },
	mBlockingCommandSent{ nullptr },
	m_ResponseMatchesLastCommand{ false },
	m_LastCommandIsBlocking{ false }
{
	mCommandTimer.setSingleShot(true);


	connect(this, &QAsyncSerialPort::messageSent, this, &QCommandSerialPort::manageMessageSent, Qt::QueuedConnection);
	connect(this, &QAsyncSerialPort::dataRead, this, &QCommandSerialPort::handleResponse, Qt::QueuedConnection);
	connect(&mCommandTimer, &QTimer::timeout, this, &QCommandSerialPort::handlePullCommandTimeout, Qt::QueuedConnection);
	connect(this, &QCommandSerialPort::developmentModeSwitched, this, &QCommandSerialPort::handleDevelopmentMode, Qt::QueuedConnection);
	connect(this, &QCommandSerialPort::disconnectRequest, this, &QCommandSerialPort::handleDisconnectRequest, Qt::QueuedConnection);
	connect(this, &QCommandSerialPort::changeSerialSettingsRequest, this, &QCommandSerialPort::handleChangeSerialSettingsRequest, Qt::QueuedConnection);
}

QCommandSerialPort::~QCommandSerialPort()
{

}


///////////////////////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////////////////////

void QCommandSerialPort::sendFromBuffer() {
	if (!mCommandsToSend.isEmpty()) {
		SerialCommand &command = mCommandsToSend[0].first;
		mCurrentOperationMode = command.operationMode();
		const QList<QVariant> &params = mCommandsToSend[0].second;
		sendMessage(command.commandToSend(params));

		m_LastCommandIsBlocking = command.operationMode().blockingMode() == SerialOperationMode::BlockingMode::Blocking;
		m_LastCommandSent = command;
	}
}

/*! Les commandes doivent impérativement être envoyées à partir d'ici pour que la gestion s'effectue correctement.
*/
void QCommandSerialPort::writeToBuffer(QPair<SerialCommand const &, QList<QVariant>> commandAndParams)
{
	mCommandsToSend.append(commandAndParams);
	if (mCommandsToSend.size() == 1 && (mCommandsSent.isEmpty() || mCommandsSent.last().first.operationMode().blockingMode() != SerialOperationMode::BlockingMode::Blocking)) {
		sendFromBuffer();
	}
	if (mCommandsToSend.size() >= mSendBufferSize) {
		emit sendBufferTooLarge();  // intercept signal
	}
}

QByteArray QCommandSerialPort::sendBlockingCommand(SerialCommand command, QList<QVariant> params)
{
	if (!m_LastCommandSent.name().isNull() && !m_LastCommandIsBlocking && !mCommandsSent.isEmpty() || !mCommandsToSend.isEmpty())
	{
		while (!m_ResponseMatchesLastCommand) {
			QCoreApplication::processEvents();
		}
		m_ResponseMatchesLastCommand = false;
	}

	mBlockingCommandSent = &command;

	QEventLoop loop;
	loop.connect(this, &QCommandSerialPort::blockingResponseReceived, &loop, &QEventLoop::quit, Qt::QueuedConnection);

	QPair<SerialCommand const &, QList<QVariant>> commandAndParams(command, params);
	writeToBuffer(commandAndParams);

	loop.exec();

	mBlockingCommandSent = nullptr;

	return mBlockingResponse;
}

/*! Compare une commande avec le tampon de réponses mResponses. S'il contient une réponse correspondante, un signal est émit et elle est retirée du tampon.
*/
//bool QCommandSerialPort::emitIfResponseMatchesCommand(QSerialCommand command) 
//{
//	QByteArray correspondingResponse = command.getFirstMatch(mResponses);
//	// if we found a response matching the command
//	if ( ! correspondingResponse.isNull()) 
//	{
//		mResponses.remove(mResponses.indexOf(correspondingResponse), correspondingResponse.length());
//		if (mWaitingForBlockingResponse)
//		{
//			mBlockingResponse = correspondingResponse;
//			emit blockingResponseReceived();
//		}
//		else
//		{
//			emit responseMatchesCommand(correspondingResponse, command);
//		}
//		return true;
//	}
//	return false;
//}

QByteArray QCommandSerialPort::responseMatchingCommand(SerialCommand command)
{
	QByteArray correspondingResponse = command.getFirstMatch(mResponses);
	// if we found a response matching the command
	if (!correspondingResponse.isNull())
	{
		mResponses.remove(mResponses.indexOf(correspondingResponse), correspondingResponse.length());
	}
	return correspondingResponse;
}

/*! À chaque réponse reçue, le tampon mResponses est analysé pour trouver toutes les réponses qui correspondent à l'une des commandes dans mCommandsSent.
*	Les tampons sont gérés en fonction du mode d'opération de chaque commande.
*
*/
void QCommandSerialPort::analyseAllResponses()
{
	CommandsAndParams::iterator commandAndParams = mCommandsSent.begin();
	while (commandAndParams != mCommandsSent.end() && !mCommandsSent.isEmpty()) {
		SerialCommand command = commandAndParams->first;
		QByteArray response = responseMatchingCommand(command);
		if (!response.isNull())
		{
			// Pull mode
			if (command.operationMode().fluxMode() == SerialOperationMode::FluxMode::Pull)
			{
				if (command.operationMode().blockingMode() == SerialOperationMode::BlockingMode::Blocking)
				{
					commandAndParams = mCommandsSent.erase(commandAndParams);
					mCommandTimer.stop(); // the response is received, so we don't want to trigger a timeout
					sendFromBuffer(); // we waited for the response, now we can send the next command
				}
				else {
					commandAndParams = mCommandsSent.erase(commandAndParams);
				}
				if (mBlockingCommandSent != nullptr && *mBlockingCommandSent == command)
				{
					mBlockingResponse = response;
					emit blockingResponseReceived();
				}
				else
				{
					emit responseMatchesCommand(response, command);
					if (command == m_LastCommandSent)
					{
						m_ResponseMatchesLastCommand = true;
					}
				}
				continue;
			}
			// Push mode
			else {
				while (!response.isNull()) {
					emit responseMatchesCommand(response, command);
					response = responseMatchingCommand(command);
				}
			}
		}
		++commandAndParams;
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

//void QCommandSerialPort::analyseAllResponses() {
//	CommandsAndParams::iterator commandAndParams = mCommandsSent.begin();
//	while (commandAndParams != mCommandsSent.end()) {
//		QSerialCommand &command = commandAndParams->first;
//		if (command.name() == "Control")
//			qDebug() << "Control";
//		if (emitIfResponseMatchesCommand(command)) {
//			// Pull mode
//			if (command.operationMode().fluxMode() == SerialOperationMode::FluxMode::Pull) 
//			{
//				if (command.operationMode().blockingMode() == SerialOperationMode::BlockingMode::Blocking) 
//				{
//					commandAndParams = mCommandsSent.erase(commandAndParams);
//					mCommandTimer.stop(); // the response is received, so we don't want to trigger a timeout
//					sendFromBuffer(); // we waited for the response, now we can send the next command
//				}
//				else {
//					commandAndParams = mCommandsSent.erase(commandAndParams);
//				}
//				continue;
//			}
//			// Push mode
//			else {
//				while (emitIfResponseMatchesCommand(command)) { ; }
//			}
//		}
//		++commandAndParams;
//	}
//	// if the device is able to send messages on its own (not a command response), and there is something left in the buffer.
//	if (!mDeviceMessages.isEmpty() && !mResponses.isEmpty()) {
//		QByteArray messages = mResponses;
//		QByteArray message = takeFirstResponse();
//		while (!message.isNull() && mDeviceMessages.contains(message)) {
//			emit messageReceived(message);
//			removeFirstResponse(message);
//			message = takeFirstResponse();
//		}
//	}
//	if (mCommandsSent.isEmpty())
//	{
//		emit bufferEmptied();
//	}
//}

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

void QCommandSerialPort::manageMessageSent() {
	if (!mDevelopmentMode && isOpen()) {
		CommandsAndParams::iterator commandAndParams = mCommandsSent.begin();
		while (commandAndParams != mCommandsSent.end()) {
			SerialCommand &command = commandAndParams->first;
			// Push mode
			if (command.operationMode().fluxMode() == SerialOperationMode::FluxMode::Push) {
				if (command.stopsPushMode(mCommandsToSend[0].first)) {
					commandAndParams = mCommandsSent.erase(commandAndParams);
					break;
				}
			}
			++commandAndParams;
		}
		if (mCurrentOperationMode.blockingMode() == SerialOperationMode::BlockingMode::NonBlockingNoResponse) {
			mCommandsToSend.removeFirst();
			sendFromBuffer();
		}
		else if (mCurrentOperationMode.blockingMode() == SerialOperationMode::BlockingMode::NonBlockingWithResponse) {
			mCommandsSent.append(mCommandsToSend.takeFirst());
			sendFromBuffer();
		}
		else {
			mCommandTimer.start(5000);
			mCommandsSent.append(mCommandsToSend.takeFirst());
		}
	}
}

void QCommandSerialPort::handleResponse(QByteArray data) {
	if (!mDevelopmentMode) {
		//mResponseTmp += "*************" + QTime::currentTime().toString() + "*************"; // Temporary test
		mResponses.append(data);
		if (mResponses.size() >= mResponsesSize) {
			emit responsesBufferTooLarge(); // intercept signal
		}
		analyseAllResponses();
	}
}

void QCommandSerialPort::handlePullCommandTimeout() {
	qDebug() << QObject::tr("Command timed out for port %1, error: %2").arg(portName()).arg(errorString()) << endl;
	QString lastCommand(mCommandsSent.last().first.name() + " (" + mCommandsSent.last().first.command() + ")");
	//if (retrySend(lastCommand)) {
	//	writeToBuffer(mCommandsSent.takeLast());
	//}
	//else {
	mCommandsSent.removeLast();
	//}
}

void QCommandSerialPort::handleDevelopmentMode(bool devMode) {
	if (devMode) {
		mCommandsToSend.clear();
		mCommandsSent.clear();
		mResponses.clear();
		mCommandTimer.stop();
	}
}

void QCommandSerialPort::closeSerialPort() {
	emit disconnectRequest();

	QEventLoop loop;
	loop.connect(this, &QCommandSerialPort::disconnectDone, &loop, &QEventLoop::quit, Qt::QueuedConnection);
	loop.exec();
}

void QCommandSerialPort::changeSerialSettings(SerialSettings * portSettings) {
	if (isOpen()) {
		emit changeSerialSettingsRequest(portSettings);

		QEventLoop loop;
		loop.connect(this, &QCommandSerialPort::changeSerialSettingsDone, &loop, &QEventLoop::quit, Qt::QueuedConnection);
		loop.exec();
	}
}

void QCommandSerialPort::handleDisconnectRequest() {
	mCommandsToSend.clear();
	mCommandsSent.clear();
	mResponses.clear();
	mCommandTimer.stop();
	QAsyncSerialPort::closeSerialPort();
	emit disconnectDone();
}

void QCommandSerialPort::handleChangeSerialSettingsRequest(SerialSettings * portSettings)
{
	handleDisconnectRequest();
	QAsyncSerialPort::openSerialPort(portSettings->mPortName, portSettings->mBaudRate, portSettings->mDataBits, portSettings->mParity, portSettings->mStopBits, portSettings->mFlowControl);
	emit changeSerialSettingsDone();
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
	mResponses.remove(mResponses.indexOf(data), data.length());
}

bool QCommandSerialPort::alreadySent(QPair<SerialCommand, QList<QVariant>> commandAndParams) const {
	for (QPair<SerialCommand, QList<QVariant>> c : mCommandsToSend) {
		if (commandAndParams.first == c.first && commandAndParams.second == c.second) {
			return true;
		}
	}
	for (QPair<SerialCommand, QList<QVariant>> c : mCommandsSent) {
		if (commandAndParams.first == c.first && commandAndParams.second == c.second) {
			return true;
		}
	}
	return false;
}