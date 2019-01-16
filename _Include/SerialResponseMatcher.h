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

	QByteArray getFirstCommandMatch(const QByteArray & responseBuffer, const SerialCommand & command) const;
	QByteArrayList getMessageMatchList(const QByteArray & responsesBuffer) const;

private:
	SerialMessages m_serialMessages;

	QByteArray getRegexMatch(const QByteArray & responsesBuffer, const SerialCommand & command) const;
	QByteArray getExpectedResponsesMatch(const QByteArray & responsesBuffer, const SerialCommand & command) const;
	QByteArray getNbExpectedBytesMatch(const QByteArray & responsesBuffer, const SerialCommand & command) const;
};

