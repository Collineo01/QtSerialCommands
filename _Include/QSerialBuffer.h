#pragma once



#include "SerialCommand.h"
#include <SerialResponseMatcher.h>

#include <QObject>
#include <QMutex>

class QSerialBuffer : public QObject
{
	Q_OBJECT

public:
	QSerialBuffer(int sendBufferSize = 10000, int responsesBufferSize = 15000, QObject * parent = nullptr);
	~QSerialBuffer();

	void removeMatchedCommand(const SerialCommand * command);
	void removeMatchedResponse(const QByteArray & matchedResponse);
	void removeNextCommandToSend();
	void moveNextCmdToSentBuffer();
	SerialCommand takeLastCommandSent();
	QList<SerialCommand>::iterator eraseSentCommand(QList<SerialCommand>::iterator it);
	QList<SerialCommand>::iterator sentCommandsBegin();
	QList<SerialCommand>::iterator sentCommandsEnd();
	void clearBuffersNow();
	int sentCommandListSize();
	QByteArray getResponseBuffer();
	SerialCommand getNextCommandToSend() const;
	bool isResponseBufferEmpty() const;

public slots:
	void writeCommand(const SerialCommand & command);
	void writeResponse(const QByteArray & response);

signals:
	void commandIsReadyToSend(SerialCommand command);
	void commandBufferFilled();
	void responseBufferFilled();

private:
	QMutex m_mutex;
	SerialResponseMatcher m_serialMatcher;
	QList<SerialCommand> m_commandToSendList;
	QList<SerialCommand> m_sentCommandList;
	QByteArray m_responseBuffer;
	QStringList m_DeviceMessages;
	unsigned int m_nbOfReadyCommands;
	int m_maxSendBufferSize;
	int m_maxResponseBufferSize;
	bool m_LastCommandIsBlocking;
	bool m_ResponseMatchesLastCommand;

	//bool retrySend(QString getCommand);
};
