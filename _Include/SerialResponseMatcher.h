#pragma once



#include <QObject>
#include <QByteArray>
#include <QMutex>
#include <SerialMessages.h>

class SerialCommand;
class QSerialBuffer;

class SerialResponseMatcher
{
public:
	SerialResponseMatcher();
	SerialResponseMatcher(const SerialMessages & serialMessages);
	~SerialResponseMatcher();

	QByteArray getFirstMatch(const SerialCommand & command, const QByteArray & responseBuffer) const;
	QByteArray takeMatchingResponse(const SerialCommand & command, QByteArray & responseBuffer) const;

private:
	SerialMessages m_serialMessages;

	QByteArray getRegexMatch(const SerialCommand & command, QByteArray const & responsesBuffer) const;
	QByteArray getExpectedResponsesMatch(const SerialCommand & command, QByteArray const & responsesBuffer) const;
	QByteArray getNbExpectedBytesMatch(const SerialCommand & command, QByteArray const & responsesBuffer) const;
};

