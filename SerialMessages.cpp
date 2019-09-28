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

void SerialMessages::mergeWith(SerialMessages serialMessages)
{
	if (m_messages.isEmpty())
	{
		m_messages = serialMessages.getMap();
	}
	else
	{
		for (QByteArray message : serialMessages.getMessageList())
		{
			insertMessage(message, serialMessages.getDescription(message));
		}
	}
}

QString SerialMessages::getDescription(QByteArray message) const
{
	return m_messages[message];
}

QString SerialMessages::getDescription(QString message) const
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

QMap<QByteArray, QString> SerialMessages::getMap() const
{
	return m_messages;
}
