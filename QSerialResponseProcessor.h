#pragma once

#include "qtserialcommands_global.h"

#include <QObject>

#include "QSerialBuffer.h"
#include "SerialCommand.h"
#include "SerialMessages.h"
#include "SerialResponseMatcher.h"


class QTSERIALCOMMANDS_EXPORT QSerialResponseProcessor : public QObject
{
	Q_OBJECT

public:
	QSerialResponseProcessor(QSerialBuffer & serialBuffer, const SerialMessages & serialMessages);
	QSerialResponseProcessor(QSerialBuffer & serialBuffer);
	~QSerialResponseProcessor();

private:
	QSerialBuffer & m_serialBuffer;
	SerialMessages m_serialMessages;
	SerialResponseMatcher m_responseMatcher;

	QByteArray takeCommandFirstMatch(const SerialCommand & command) const;
	void takeMessages();

public slots:
	void processResponses();

signals:
	void foundMatchingResponse(const QByteArray & response, const SerialCommand & command);
	void foundMessage(const QByteArray & message, const QString & description);
	void commandIsReadyToSend(const SerialCommand & command);
};
