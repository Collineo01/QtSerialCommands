#pragma once

#include "qtserialcommands_global.h"

#include "SerialPortSettings.h"

class QTSERIALCOMMANDS_EXPORT DefaultSerialPortSettings :
	public SerialPortSettings
{
public:
	DefaultSerialPortSettings();
	DefaultSerialPortSettings(int port);
	~DefaultSerialPortSettings();
};

