#pragma once

/*!	\class QMatchSerialPort
*
*	\brief G�re les tampons d'envoi de commandes et de r�ponses.
*
*
*	Permet d'envoyer des SerialCommand et d'analyser les r�ponses. Quand une r�ponse correspond � un SerialCommand envoy�e,
*	ceux-ci sont retir�s de leur tampon respectif et le signal matchingResponseReceived() est �mit.
*	Si l'appareil connect� peut envoyer des messages de lui m�me, il faut appeler la fonction setDeviceMessages()
*	afin de les reconna�tre pour �mettre le signal messageReceived() quand un message est re�u.
*	La gestion des tampons d'envoie d�pend de chaque mode d'op�ration des SerialCommand envoy�s.
*
*
*	D�tails concernant les modes d'op�ration:
*
*	-SerialCommand avec mode d'op�ration OperationMode::BlockingMode::Blocking : quand la r�ponse attendue sera re�ue,
*		la commande et la r�ponse seront retir�es de leur tampon, et la prochaine commande dans le tampon m_commandToSendList sera envoy�e.
*	-SerialCommand avec mode d'op�ration OperationMode::BlockingMode::NonBlockingWithResponse : une fois envoy�, le prochain SerialCommand dans m_commandToSendList sera directement envoy�.
*		Quand la r�ponse correspondante du premier est re�ue, il sera retir� du tampon m_sentCommandList.
*	-SerialCommand avec mode d'op�ration OperationMode::BlockingMode::NonBlockingNoResponse : une fois envoy�, le prochain SerialCommand dans m_commandToSendList sera directement envoy�.
*
*	-SerialCommand avec mode d'op�ration OperationMode::FluxMode::Push : des r�ponses en continue sont attendues jusqu'� ce que la commande qui l'arr�te soit envoy�e.
*		*Cette commande devra �tre ajout� � l'aide de la m�thode addPushModeStopCommand() dans le SerialCommand en mode Push. Il sera alors retir� du tampon m_sentCommandList.
*	-SerialCommand avec mode d'op�ration OperationMode::FluxMode::Pull : au maximum une r�ponse est attendue.
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
