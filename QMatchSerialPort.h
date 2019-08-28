#pragma once

/*!	\class QMatchSerialPort
*
*	\brief Gère les tampons d'envoi de commandes et de réponses.
*
*
*	Permet d'envoyer des SerialCommand et d'analyser les réponses. Quand une réponse correspond à un SerialCommand envoyée,
*	ceux-ci sont retirés de leur tampon respectif et le signal matchingResponseReceived() est émit.
*	Si l'appareil connecté peut envoyer des messages de lui même, il faut appeler la fonction setDeviceMessages()
*	afin de les reconnaître pour émettre le signal messageReceived() quand un message est reçu.
*	La gestion des tampons d'envoie dépend de chaque mode d'opération des SerialCommand envoyés.
*
*
*	Détails concernant les modes d'opération:
*
*	-SerialCommand avec mode d'opération OperationMode::BlockingMode::Blocking : quand la réponse attendue sera reçue,
*		la commande et la réponse seront retirées de leur tampon, et la prochaine commande dans le tampon m_commandToSendList sera envoyée.
*	-SerialCommand avec mode d'opération OperationMode::BlockingMode::NonBlockingWithResponse : une fois envoyé, le prochain SerialCommand dans m_commandToSendList sera directement envoyé.
*		Quand la réponse correspondante du premier est reçue, il sera retiré du tampon m_sentCommandList.
*	-SerialCommand avec mode d'opération OperationMode::BlockingMode::NonBlockingNoResponse : une fois envoyé, le prochain SerialCommand dans m_commandToSendList sera directement envoyé.
*
*	-SerialCommand avec mode d'opération OperationMode::FluxMode::Push : des réponses en continue sont attendues jusqu'à ce que la commande qui l'arrête soit envoyée.
*		*Cette commande devra être ajouté à l'aide de la méthode addPushModeStopCommand() dans le SerialCommand en mode Push. Il sera alors retiré du tampon m_sentCommandList.
*	-SerialCommand avec mode d'opération OperationMode::FluxMode::Pull : au maximum une réponse est attendue.
*/

#include "qtserialcommands_global.h"

#include <QList>
#include "QAsyncSerialPort.h"
#include "SerialCommand.h"
#include "SerialPortSettings.h"

#include "QSerialBuffer.h"
#include "QSerialResponseProcessor.h"
#include "SerialMessageFactory.h"

class QVariant;
class QStringList;


class QTSERIALCOMMANDS_EXPORT QMatchSerialPort : public QAsyncSerialPort
{
	Q_OBJECT

public:
	QMatchSerialPort(
		const SerialPortSettings & settings, 
		const SerialMessageFactory & serialMessagesFactory, 
		bool isAutoReconnecting = false
	);
	QMatchSerialPort(const SerialPortSettings & settings, bool isAutoReconnecting = false);
	QMatchSerialPort(const SerialMessageFactory & serialMessagesFactory, bool isAutoReconnecting = false);
	QMatchSerialPort(bool isAutoReconnecting = false);
	~QMatchSerialPort();

	void sendCommand(SerialCommand command, QList<SerialCommandArg> args = QList<SerialCommandArg>());
	QByteArray sendCommandAwait(SerialCommand command, QList<SerialCommandArg> args = QList<SerialCommandArg>());
	bool isBypassingSmartMatching() const { return m_bypassSmartMatchingMode; }
	void setBypassSmartMatchingMode(bool isBypassing);
	void closePort() override;

private:
	QSerialBuffer m_serialBuffer;
	const SerialMessages & m_serialMessages;
	bool m_autoReconnect;
	bool m_gotDisconnected;
	bool m_hasChangedSettings;
	QTimer m_commandTimer;
	bool m_bypassSmartMatchingMode;
	SerialCommand * m_commandToSend;
	QByteArray m_syncBlockingResponse;

private slots:
	void handleNextCommandReadyToSend();
	void handleFoundMatchingResponse(const QByteArray & response, const SerialCommand & command);
	void handleResponse(QByteArray data);
	void handlePullCommandTimeout();
	void handleSmartMatchingModeChange(bool isBypassing);
	void handleSendCommandRequest(const SerialCommand & command);

signals:
	void sendCommandRequested(const SerialCommand & command);
	void matchingResponseReceived(const QByteArray & response, const SerialCommand & command);
	void messageReceived(const QByteArray & message, const QString & translation);
	void smartMatchingModeChanged(bool devMode);
	void commandTimedOut(QString command, QList<SerialCommandArg> args, int port);
	void removeLastCommandSentRequest();
	void removeFirstCommandToSendRequest();
};
