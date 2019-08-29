#pragma once

#include "qtserialcommands_global.h"

#include <QMap>
#include <QString>
#include <QByteArray>

class QTSERIALCOMMANDS_EXPORT SerialMessages
{
public:
	SerialMessages();
	~SerialMessages();

	void insertMessage(QByteArray message, QString description = "");
	QString getDescription(QByteArray message) const;
	QByteArrayList getMessageList() const;
	bool isEmpty() const;

private:
	QMap<QByteArray, QString> m_messages;
};
