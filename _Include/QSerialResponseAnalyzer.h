#pragma once



#include <QObject>

#include "QSerialBuffer.h"
#include "SerialCommand.h"
#include "SerialMessages.h"
#include "SerialResponseMatcher.h"


class QSerialResponseAnalyzer : public QObject
{
	Q_OBJECT

public:
	QSerialResponseAnalyzer(QSerialBuffer & serialBuffer, const SerialMessages & serialMessages);
	QSerialResponseAnalyzer(QSerialBuffer & serialBuffer);
	~QSerialResponseAnalyzer();
	QByteArray takeMatchingResponse(const SerialCommand & command);

public slots:
	void analyzeResponses();

signals:
	void foundMatchingResponse(const QByteArray & response, const SerialCommand & command);
	void foundMessage(const QByteArray & message, const QString & translation);
	void commandIsReadyToSend(const SerialCommand & command);

private:
	QSerialBuffer & m_serialBuffer;
	SerialMessages m_serialMessages;
	SerialResponseMatcher m_responseMatcher;
};
