#include "SerialPortSettings.h"

#include <QSettings>

const QString SerialPortSettings::KEY_PORT{ "getPort" };
const QString SerialPortSettings::KEY_BAUDRATE{ "baudRate" };
const QString SerialPortSettings::KEY_STOPBITS{ "stopBits" };
const QString SerialPortSettings::KEY_DATABITS{ "dataBits" };
const QString SerialPortSettings::KEY_PARITY{ "parity" };
const QString SerialPortSettings::KEY_FLOWCONTROL{ "flowControl" };

const QAsyncSerialPort::BaudRate SerialPortSettings::DEFAULT_BAUD_RATE{ QAsyncSerialPort::BaudRate::BR9600 };
const QAsyncSerialPort::DataBits SerialPortSettings::DEFAULT_DATA_BITS{ QAsyncSerialPort::DataBits::Data8 };
const QAsyncSerialPort::StopBits SerialPortSettings::DEFAULT_STOP_BITS{ QAsyncSerialPort::StopBits::OneStop };
const QAsyncSerialPort::Parity SerialPortSettings::DEFAULT_PARITY{ QAsyncSerialPort::Parity::NoParity };
const QAsyncSerialPort::FlowControl SerialPortSettings::DEFAULT_FLOW_CONTROL{ QAsyncSerialPort::FlowControl::NoFlowControl };


SerialPortSettings::SerialPortSettings(
	int port,
	QAsyncSerialPort::BaudRate baudRate,
	QAsyncSerialPort::StopBits stopBits,
	QAsyncSerialPort::DataBits dataBits,
	QAsyncSerialPort::Parity parity,
	QAsyncSerialPort::FlowControl flowControl
) :
	m_Port{ port },
	m_BaudRate{ baudRate },
	m_StopBits{ stopBits },
	m_DataBits{ dataBits },
	m_Parity{ parity },
	m_FlowControl{ flowControl }
{
}

void SerialPortSettings::save(QString fileName) {
	QSettings settings(fileName + ".ini", QSettings::Format::IniFormat);
	settings.setValue(KEY_PORT, static_cast<int>(m_Port));
	settings.setValue(KEY_BAUDRATE, static_cast<int>(m_BaudRate));
	settings.setValue(KEY_STOPBITS, m_StopBits);
	settings.setValue(KEY_DATABITS, m_DataBits);
	settings.setValue(KEY_PARITY, m_Parity);
	settings.setValue(KEY_FLOWCONTROL, m_FlowControl);
}

void SerialPortSettings::load(QString fileName) {
	QSettings settings(fileName + ".ini", QSettings::Format::IniFormat);
	m_Port = settings.value(KEY_PORT).toInt();
	m_BaudRate = static_cast<QAsyncSerialPort::BaudRate>(settings.value(KEY_BAUDRATE).toInt());
	m_StopBits = static_cast<QAsyncSerialPort::StopBits>(settings.value(KEY_STOPBITS).toInt());
	m_DataBits = static_cast<QAsyncSerialPort::DataBits>(settings.value(KEY_DATABITS).toInt());
	m_Parity = static_cast<QAsyncSerialPort::Parity>(settings.value(KEY_PARITY).toInt());
	m_FlowControl = static_cast<QAsyncSerialPort::FlowControl>(settings.value(KEY_FLOWCONTROL).toInt());
}

bool SerialPortSettings::isValid() {
	if (m_Port <= 0) {
		return false;
	}
	if (m_BaudRate == QAsyncSerialPort::BaudRate::BRUnknown) {
		return false;
	}
	if (m_StopBits == QAsyncSerialPort::StopBits::UnknownStopBits) {
		return false;
	}
	if (m_DataBits == QAsyncSerialPort::DataBits::UnknownDataBits) {
		return false;
	}
	if (m_Parity == QAsyncSerialPort::Parity::UnknownParity) {
		return false;
	}
	if (m_FlowControl == QAsyncSerialPort::FlowControl::UnknownFlowControl) {
		return false;
	}

	return true;
}

