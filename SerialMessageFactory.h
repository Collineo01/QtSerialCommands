#pragma once

#include "qtserialcommands_global.h"

#include "SerialMessages.h"

class QTSERIALCOMMANDS_EXPORT SerialMessageFactory
{
public:
	SerialMessageFactory() {}
	virtual ~SerialMessageFactory() {};

	virtual SerialMessages createSerialMessages() const { return SerialMessages(); };
};
