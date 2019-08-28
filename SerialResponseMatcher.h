#pragma once

#include "qtserialcommands_global.h"

#include "SerialCommand.h"
#include "SerialMessages.h"

#include <QByteArray>

class QTSERIALCOMMANDS_EXPORT SerialResponseMatcher
{
public:
	SerialResponseMatcher();
	SerialResponseMatcher(const SerialMessages & serialMessages);
	~SerialResponseMatcher();

	QByteArray getCommandFirstMatch(const QByteArray & responseBuffer, const SerialCommand & command) const;
	QByteArrayList getMessages(const QByteArray & responsesBuffer) const;

private:
	SerialMessages m_serialMessages;

	QByteArray getRegexMatch(const QByteArray & responsesBuffer, const SerialCommand & command) const;
	QByteArray getExpectedResponsesMatch(const QByteArray & responsesBuffer, const SerialCommand & command) const;
	QByteArray getNbExpectedBytesMatch(const QByteArray & responsesBuffer, const SerialCommand & command) const;
};

