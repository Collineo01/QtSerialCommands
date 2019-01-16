#pragma once



#include "SerialMessages.h"

class SerialMessageFactory
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

