#pragma once

#include "qtserialcommands_global.h"

#include "SerialCommand.h"

#include <QMap>
#include <QList>
#include <QString>

class QTSERIALCOMMANDS_EXPORT SerialCommandFactory
{
public:
	SerialCommandFactory() {}
	virtual ~SerialCommandFactory() {};

	virtual QMap<QString, const SerialCommand*> createCommands() const { return QMap<QString, const SerialCommand*>(); };
	virtual QList<const SerialCommand*> createEmergencyCommands() const { return QList<const SerialCommand*>(); };
};