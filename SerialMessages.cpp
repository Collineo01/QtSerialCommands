#include "SerialMessages.h"


SerialMessages::SerialMessages()
{
}

SerialMessages::~SerialMessages()
{
}

void SerialMessages::insertMessage(QByteArray message, QString description)
{
	m_messages.insert(message, description);
}

QString SerialMessages::getDescription(QByteArray message) const
{
	return m_messages[message];
}

QByteArrayList SerialMessages::getMessageList() const
{
	return m_messages.keys();
}

bool SerialMessages::isEmpty() const
{
	return m_messages.isEmpty();
}