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
	void mergeWith(SerialMessages serialMessages);
	QString getDescription(QByteArray message) const;
	QString getDescription(QString message) const;
	QByteArrayList getMessageList() const;
	bool isEmpty() const;

	QMap<QByteArray, QString> getMap() const;

private:
	QMap<QByteArray, QString> m_messages;
};
