#include "DefaultSerialPortSettings.h"


DefaultSerialPortSettings::DefaultSerialPortSettings() :
	SerialPortSettings{
		INVALID_PORT,
		BaudRate::BR9600,
		QSerialPort::StopBits::OneStop,
		QSerialPort::DataBits::Data8,
		QSerialPort::Parity::NoParity,
		QSerialPort::FlowControl::NoFlowControl
	}
{
}

DefaultSerialPortSettings::DefaultSerialPortSettings(int port) :
	SerialPortSettings{
		port,
		BaudRate::BR9600,
		QSerialPort::StopBits::OneStop,
		QSerialPort::DataBits::Data8,
		QSerialPort::Parity::NoParity,
		QSerialPort::FlowControl::NoFlowControl
}
{
}


DefaultSerialPortSettings::~DefaultSerialPortSettings()
{
}
