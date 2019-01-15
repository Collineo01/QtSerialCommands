#pragma once



#include "SerialCommand.h";

class SerialCommandFactory
{
public:
	SerialCommandFactory();
	virtual ~SerialCommandFactory();

	virtual QMap<QString, const SerialCommand *> createSerialCommands() const = 0;
};

