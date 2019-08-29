#pragma once

#include "qtserialcommands_global.h"

#include <QSerialPort>
#include "BaudRate.h"

/*! \class SerialPortSettings
*/


class QTSERIALCOMMANDS_EXPORT SerialPortSettings
{

public:
	static const QString KEY_PORT;
	static const QString KEY_BAUDRATE;
	static const QString KEY_STOPBITS;
	static const QString KEY_DATABITS;
	static const QString KEY_PARITY;
	static const QString KEY_FLOWCONTROL;

	static const int						INVALID_PORT;

	static const BaudRate					DEFAULT_BAUD_RATE;
	static const QSerialPort::StopBits		DEFAULT_STOP_BITS;
	static const QSerialPort::DataBits		DEFAULT_DATA_BITS;
	static const QSerialPort::Parity		DEFAULT_PARITY;
	static const QSerialPort::FlowControl	DEFAULT_FLOW_CONTROL;

	SerialPortSettings(
		int port,
		BaudRate baudRate = DEFAULT_BAUD_RATE,
		QSerialPort::StopBits stopBits = DEFAULT_STOP_BITS,
		QSerialPort::DataBits dataBits = DEFAULT_DATA_BITS,
		QSerialPort::Parity parity = DEFAULT_PARITY,
		QSerialPort::FlowControl flowControl = DEFAULT_FLOW_CONTROL
	);
	SerialPortSettings();
	~SerialPortSettings();

	void save(QString fileName);
	void load(QString fileName);
	bool isValid();

	SerialPortSettings baudRate(BaudRate baudRate);

	int getPort() const { return m_port; }
	BaudRate getBaudRate() const { return m_baudRate; }
	QSerialPort::StopBits  getStopBits() const { return m_stopBits; }
	QSerialPort::DataBits getDataBits() const { return m_dataBits; }
	QSerialPort::Parity getParity() const { return m_parity; }
	QSerialPort::FlowControl getFlowControl() const { return m_flowControl; }

	void setPort(int port) { m_port = port; }

protected:
	int m_port;
	BaudRate m_baudRate;
	QSerialPort::StopBits m_stopBits;
	QSerialPort::DataBits m_dataBits;
	QSerialPort::Parity m_parity;
	QSerialPort::FlowControl m_flowControl;
};