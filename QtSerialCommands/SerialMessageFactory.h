#pragma once

#include "qtserialcommands_global.h"

#include "SerialMessages.h"

class QTSERIALCOMMANDS_EXPORT SerialMessageFactory
{
public:
	SerialMessageFactory() {}
	virtual ~SerialMessageFactory();

	virtual SerialMessages createSerialMessages() const = 0;
};

class DummySerialMessageFactory : public SerialMessageFactory
{
public:
	DummySerialMessageFactory() : SerialMessageFactory() {}
	~DummySerialMessageFactory() = default;
	SerialMessages createSerialMessages() const override { return SerialMessages(); }
};

