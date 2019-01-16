#pragma once



#include <QMap>
#include <QString>
#include <QByteArray>

class SerialMessages
{
public:
	SerialMessages();
	~SerialMessages();

	void insertMessage(QByteArray message, QString translation = "");
	void insertMessage(QString message, QString translation = "");
	QString getTranslation(QByteArray message) const;
	QString getTranslation(QString message) const;
	QByteArrayList getMessageList() const;
	bool isEmpty() const;

private:
	QMap<QByteArray, QString> m_messages;
};
