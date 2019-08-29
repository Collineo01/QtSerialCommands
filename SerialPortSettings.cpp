#include "SerialPortSettings.h"

#include <QSettings>

const QString SerialPortSettings::KEY_PORT{ "getPort" };
const QString SerialPortSettings::KEY_BAUDRATE{ "baudRate" };
const QString SerialPortSettings::KEY_STOPBITS{ "stopBits" };
const QString SerialPortSettings::KEY_DATABITS{ "dataBits" };
const QString SerialPortSettings::KEY_PARITY{ "parity" };
const QString SerialPortSettings::KEY_FLOWCONTROL{ "flowControl" };

const int SerialPortSettings::INVALID_PORT{ -1 };

const BaudRate SerialPortSettings::DEFAULT_BAUD_RATE{ BaudRate::BR9600 };
const QSerialPort::DataBits SerialPortSettings::DEFAULT_DATA_BITS{ QSerialPort::DataBits::Data8 };
const QSerialPort::StopBits SerialPortSettings::DEFAULT_STOP_BITS{ QSerialPort::StopBits::OneStop };
const QSerialPort::Parity SerialPortSettings::DEFAULT_PARITY{ QSerialPort::Parity::NoParity };
const QSerialPort::FlowControl SerialPortSettings::DEFAULT_FLOW_CONTROL{ QSerialPort::FlowControl::NoFlowControl };


SerialPortSettings::SerialPortSettings(
	int port,
	BaudRate baudRate,
	QSerialPort::StopBits stopBits,
	QSerialPort::DataBits dataBits,
	QSerialPort::Parity parity,
	QSerialPort::FlowControl flowControl
) :
	m_port{ port },
	m_baudRate{ baudRate },
	m_stopBits{ stopBits },
	m_dataBits{ dataBits },
	m_parity{ parity },
	m_flowControl{ flowControl }
{
}

SerialPortSettings::SerialPortSettings():
	SerialPortSettings(-1)
{
}

SerialPortSettings::~SerialPortSettings()
{
}

void SerialPortSettings::save(QString fileName) {
	QSettings settings(fileName + ".ini", QSettings::Format::IniFormat);
	settings.setValue(KEY_PORT, static_cast<int>(m_port));
	settings.setValue(KEY_BAUDRATE, static_cast<int>(m_baudRate));
	settings.setValue(KEY_STOPBITS, m_stopBits);
	settings.setValue(KEY_DATABITS, m_dataBits);
	settings.setValue(KEY_PARITY, m_parity);
	settings.setValue(KEY_FLOWCONTROL, m_flowControl);
}

void SerialPortSettings::load(QString fileName) {
	QSettings settings(fileName + ".ini", QSettings::Format::IniFormat);
	m_port = settings.value(KEY_PORT).toInt();
	m_baudRate = static_cast<BaudRate>(settings.value(KEY_BAUDRATE).toInt());
	m_stopBits = static_cast<QSerialPort::StopBits>(settings.value(KEY_STOPBITS).toInt());
	m_dataBits = static_cast<QSerialPort::DataBits>(settings.value(KEY_DATABITS).toInt());
	m_parity = static_cast<QSerialPort::Parity>(settings.value(KEY_PARITY).toInt());
	m_flowControl = static_cast<QSerialPort::FlowControl>(settings.value(KEY_FLOWCONTROL).toInt());
}

bool SerialPortSettings::isValid() {
	if (m_port <= 0) {
		return false;
	}
	if (m_baudRate == BaudRate::BRUnknown) {
		return false;
	}
	if (m_stopBits == QSerialPort::StopBits::UnknownStopBits) {
		return false;
	}
	if (m_dataBits == QSerialPort::DataBits::UnknownDataBits) {
		return false;
	}
	if (m_parity == QSerialPort::Parity::UnknownParity) {
		return false;
	}
	if (m_flowControl == QSerialPort::FlowControl::UnknownFlowControl) {
		return false;
	}

	return true;
}

SerialPortSettings SerialPortSettings::baudRate(BaudRate baudRate)
{
	m_baudRate = baudRate;
	return *this;
}

