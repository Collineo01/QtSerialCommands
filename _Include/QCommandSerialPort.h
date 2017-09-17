/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/

/*!	\class QCommandSerialPort
*
*	\brief Gère les tampons d'envoi de commandes et de réponses.
*
*
*	Permet d'envoyer des QSerialCommand et d'analyser les réponses. Quand une réponse correspond à un QSerialCommand envoyée,
*	ceux-ci sont retirés de leur tampon respectif et le signal responseMatchesCommand() est émit.
*	Si l'appareil connecté peut envoyer des messages de lui même, il faut appeler la fonction setDeviceMessages()
*	afin de les reconnaître pour émettre le signal messageReceived() quand un message est reçu.
*	La gestion des tampons d'envoie dépend de chaque mode d'opération des QSerialCommand envoyés.
*
*
*	Détails concernant les modes d'opération:
*
*	-QSerialCommand avec mode d'opération OperationMode::BlockingMode::Blocking : quand la réponse attendue sera reçue,
*		la commande et la réponse seront retirées de leur tampon, et la prochaine commande dans le tampon mCommandsToSend sera envoyée.
*	-QSerialCommand avec mode d'opération OperationMode::BlockingMode::NonBlockingWithResponse : une fois envoyé, le prochain QSerialCommand dans mCommandsToSend sera directement envoyé.
*		Quand la réponse correspondante du premier est reçue, il sera retiré du tampon mCommandsSent.
*	-QSerialCommand avec mode d'opération OperationMode::BlockingMode::NonBlockingNoResponse : une fois envoyé, le prochain QSerialCommand dans mCommandsToSend sera directement envoyé.
*
*	-QSerialCommand avec mode d'opération OperationMode::FluxMode::Push : des réponses en continue sont attendues jusqu'à ce que la commande qui l'arrête soit envoyée.
*		*Cette commande devra être ajouté à l'aide de la méthode addPushModeStopCommand() dans le QSerialCommand en mode Push. Il sera alors retiré du tampon mCommandsSent.
*	-QSerialCommand avec mode d'opération OperationMode::FluxMode::Pull : au maximum une réponse est attendue.
*/


#ifndef QCOMMANDSERIALPORT_H
#define QCOMMANDSERIALPORT_H



#include <QList>
#include <QPair>
#include "QAsyncSerialPort.h"
#include "SerialCommand.h"



class QVariant;
class QStringList;


class QCommandSerialPort : public QAsyncSerialPort
{
	Q_OBJECT

public:
	QCommandSerialPort(int sendBufferSize = 150, int responsesBufferSize = 15000); //change name
	~QCommandSerialPort();

	QList<SerialCommand> mCommandsToSend;// private (return const ref)
	QList<SerialCommand> mCommandsSent;
	QByteArray mResponses;
	SerialOperationMode mCurrentOperationMode;

	bool developmentMode() { return mDevelopmentMode; }
	void setDevelopmentMode(bool devMode);
	void setDeviceMessages(QStringList messages, QString terminator);

	void changeSerialSettings(SerialSettings * portSettings);

	void removeLastCommandSent();
	void clearBuffers();

private:
	QStringList mDeviceMessages;
	QString mTerminator;
	QTimer mCommandTimer;
	int mSendBufferSize;
	int mResponsesSize;
	bool mDevelopmentMode;
	SerialCommand * mBlockingCommandSent;

	SerialCommand m_LastCommandSent;
	bool m_LastCommandIsBlocking;
	bool m_ResponseMatchesLastCommand;

	bool m_GotDisconnected;
	bool m_HasChangedSettings;

	QByteArray mBlockingResponse;

	void sendFromBuffer();
	void readData();
	void analyseAllResponses();
	//bool emitIfResponseMatchesCommand(QSerialCommand command);
	QByteArray responseMatchingCommand(SerialCommand command);

	QByteArray takeFirstResponse();
	void removeFirstResponse(QByteArray data);
	//bool retrySend(QString command);
	bool alreadySent(SerialCommand command) const;
	
	void clearBuffersNow();

public slots:
	void writeToBuffer(SerialCommand const & command);
	QByteArray sendBlockingCommand(SerialCommand command, QList<QVariant> params);
	void manageMessageSent();
	virtual void closeSerialPort() override;

private slots:
	void handleResponse(QByteArray data);
	void handlePullCommandTimeout();
	void handleDevelopmentMode(bool devMode);
	void handleDisconnectRequest();
	void handleChangeSerialSettingsRequest(SerialSettings * portSettings);
	void handleClearBuffersRequest();
	void handleRemoveLastCommandSent();
	void handleRemoveFirstCommandToSend();
	void handleSendCommandRequest(SerialCommand command);

signals:
	void responseMatchesCommand(QByteArray response, SerialCommand command);
	void messageReceived(QString message);
	void developmentModeSwitched(bool devMode);
	void sendBufferTooLarge(); //
	void responsesBufferTooLarge();
	void disconnectRequest();
	void disconnectDone();
	void blockingResponseReceived();
	void changeSerialSettingsRequest(SerialSettings * portSettings);
	void changeSerialSettingsDone();
	void commandTimeout(SerialCommand command, int port);
	void clearBuffersRequest();
	void removeLastCommandSentRequest();
	void removeFirstCommandToSendRequest();
	void sendCommandRequest(SerialCommand command);
};


#endif // QCOMMANDSERIALPORT_H

