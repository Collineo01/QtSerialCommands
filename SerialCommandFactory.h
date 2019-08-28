#pragma once

#include "qtserialcommands_global.h"

#include "SerialCommand.h"

#include <QMap>
#include <QString>

class QTSERIALCOMMANDS_EXPORT SerialCommandFactory
{
public:
	virtual QMap<QString, const SerialCommand *> createSerialCommands() const = 0;
};

