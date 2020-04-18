#pragma once

#include "qtserialcommands_global.h"

#include "SerialCommand.h"
#include "SerialResponseMatcher.h"

#include <QObject>
#include <QMutex>

class QTSERIALCOMMANDS_EXPORT QSerialBuffer : public QObject
{
	Q_OBJECT

public:
	QSerialBuffer(int sendBufferSize = 10000, int responsesBufferSize = 15000, QObject * parent = nullptr);
	~QSerialBuffer();

	bool removeMatchedCommand(const SerialCommand & command);
	void removeMatchedResponse(const QByteArray & matchedResponse);
	void removeMatchedResponses(const QByteArrayList & matchedResponses);
	void removeNextCommandToSend();
	QList<SerialCommand>::iterator getSentCommandsBegin();
	QList<SerialCommand>::iterator getSentCommandsEnd();
	SerialCommand takeLastCommandSent();
	QList<SerialCommand>::iterator eraseSentCommand(QList<SerialCommand>::iterator it);
	void clearBuffers();
	int getSentCommandListSize();
	QByteArray getResponseBuffer();
	bool hasNextCommandToSend();
	SerialCommand getNextCommandToSend();
	bool isResponseBufferEmpty();
	void handleSentCommandToSend();

public slots:
	void writeCommand(SerialCommand command);
	void writeResponse(const QByteArray & response);

signals:
	void nextCommandReadyToSend();
	void commandBufferFilled();
	void responseBufferFilled();

private:
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
