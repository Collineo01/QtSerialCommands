#pragma once

#include "qtserialcommands_global.h"

#include "SerialCommand.h";

class QTSERIALCOMMANDS_EXPORT SerialCommandFactory
{
public:
	SerialCommandFactory();
	virtual ~SerialCommandFactory();

	virtual QMap<QString, const SerialCommand *> createSerialCommands() const = 0;
};

