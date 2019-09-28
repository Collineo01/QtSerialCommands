#pragma once

/*!	\class QMatchSerialPort
*/

#include "qtserialcommands_global.h"

#include "QAsyncSerialPort.h"
#include "SerialCommand.h"
#include "SerialPortSettings.h"
#include "QSerialBuffer.h"
#include "QSerialResponseProcessor.h"
#include "SerialCommandFactory.h"
#include "SerialMessageFactory.h"

#include <QList>
#include <QThread>

class QVariant;
class QStringList;


class QTSERIALCOMMANDS_EXPORT QCommandSerialPort : public QAsyncSerialPort
{
	Q_OBJECT

public:
	QCommandSerialPort(
		const SerialPortSettings & settings, 
		const QList<SerialMessageFactory> & serialMessageFactories = {},
		bool isAutoReconnecting = false
	);
	~QCommandSerialPort();

	void sendCommand(SerialCommand command, QList<SerialCommandArg> args = QList<SerialCommandArg>());
	QByteArray sendCommandAwait(SerialCommand command, QList<SerialCommandArg> args = QList<SerialCommandArg>());
	bool isBypassingSmartMatching() const { return m_bypassSmartMatchingMode; }
	void setBypassSmartMatchingMode(bool isBypassing);
	void closePort() override;
	void softResetPort();
	void hardResetPort();
	void clearBuffers();

private:
	QSerialBuffer m_serialBuffer;
	SerialMessages m_serialMessages;

	QThread m_responseProcessingThread;
	QSerialResponseProcessor m_responseProcessor;

	bool m_autoReconnect;
	bool m_gotDisconnected;
	bool m_hasChangedSettings;
	QTimer m_commandTimer;
	bool m_bypassSmartMatchingMode;
	SerialCommand * m_commandToSendAwait;
	QByteArray m_awaitedResponse;

private slots:
	void handleNextCommandReadyToSend();
	void handleFoundMatchingResponse(const QByteArray & response, const SerialCommand & command);
	void handleResponse(QByteArray data);
	void handlePullCommandTimeout();
	void handleSmartMatchingModeChange(bool isBypassing);

signals:
	void sendCommandRequested(const SerialCommand & command);
	void matchingResponseReceived(const QByteArray & response, const SerialCommand & command);
	void messageReceived(const QByteArray & message, const QString & translation);
	void smartMatchingModeChanged(bool devMode);
	void commandTimedOut(QString command, QList<SerialCommandArg> args, int port);
	void removeLastCommandSentRequested();
	void removeFirstCommandToSendRequested();
	void processResponsesRequested();
};
