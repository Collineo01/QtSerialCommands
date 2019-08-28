#include "SerialMessages.h"


SerialMessages::SerialMessages()
{
}

SerialMessages::~SerialMessages()
{
}

void SerialMessages::insertMessage(QByteArray message, QString translation)
{
	m_messages.insert(message, translation);
}

void SerialMessages::insertMessage(QString message, QString translation)
{
	m_messages.insert(message.toLatin1(), translation);
}

QString SerialMessages::getTranslation(QByteArray message) const
{
	return m_messages[message];
}

QString SerialMessages::getTranslation(QString message) const
{
	return m_messages[message.toLatin1()];
}

QByteArrayList SerialMessages::getMessageList() const
{
	return m_messages.keys();
}

bool SerialMessages::isEmpty() const
{
	return m_messages.isEmpty();
}