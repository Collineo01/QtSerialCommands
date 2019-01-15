#pragma once



#include <QString>;
#include <QMap>;

#include "SerialMessages.h"

class SerialMessageFactory
{
public:
	QString m_messageTerminator;

	SerialMessageFactory(QString messageTerminator) : m_messageTerminator{ messageTerminator } {}
	virtual ~SerialMessageFactory();

	virtual SerialMessages createSerialMessages() const = 0;
	QString getMessageTerminator() const { return m_messageTerminator; }
};

class DummySerialMessageFactory : public SerialMessageFactory
{
public:
	DummySerialMessageFactory() : SerialMessageFactory("") {}
	~DummySerialMessageFactory() = default;
	SerialMessages createSerialMessages() const override { return SerialMessages(); }
};

