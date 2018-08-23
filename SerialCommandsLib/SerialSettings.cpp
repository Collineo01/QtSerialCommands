#include "SerialSettings.h"

#include <QSettings>



QString const SerialSettings::KEY_PORT{ "port" };
QString const SerialSettings::KEY_BAUDRATE{ "baudRate" };
QString const SerialSettings::KEY_STOPBITS{ "stopBits" };
QString const SerialSettings::KEY_DATABITS{ "dataBits" };
QString const SerialSettings::KEY_PARITY{ "parity" };
QString const SerialSettings::KEY_FLOWCONTROL{ "flowControl" };


SerialSettings::SerialSettings(QAsyncSerialPort::BaudRate baudRate)
	:
	m_BaudRate{ baudRate }
{
	loadGeneric();
}

SerialSettings::SerialSettings(int port, QAsyncSerialPort::BaudRate baudRate)
	:
	m_Port{ port },
	m_BaudRate{ baudRate },
	m_StopBits{ QSerialPort::StopBits::OneStop },
	m_DataBits{ QSerialPort::DataBits::Data8 },
	m_Parity{ QSerialPort::Parity::NoParity },
	m_FlowControl{ QSerialPort::FlowControl::NoFlowControl }
{

}

SerialSettings::~SerialSettings() {

}

void SerialSettings::save(QString fileName) {
	QSettings settings(fileName + ".ini", QSettings::Format::IniFormat);
	settings.setValue(KEY_PORT, static_cast<int>(m_Port));
	settings.setValue(KEY_BAUDRATE, static_cast<int>(m_BaudRate));
	settings.setValue(KEY_STOPBITS, m_StopBits);
	settings.setValue(KEY_DATABITS, m_DataBits);
	settings.setValue(KEY_PARITY, m_Parity);
	settings.setValue(KEY_FLOWCONTROL, m_FlowControl);
}

void SerialSettings::load(QString fileName) {
	QSettings settings(fileName + ".ini", QSettings::Format::IniFormat);
	m_Port = settings.value(KEY_PORT).toInt();
	m_BaudRate = static_cast<QAsyncSerialPort::BaudRate>(settings.value(KEY_BAUDRATE).toInt());
	m_StopBits = static_cast<QSerialPort::StopBits>(settings.value(KEY_STOPBITS).toInt());
	m_DataBits = static_cast<QSerialPort::DataBits>(settings.value(KEY_DATABITS).toInt());
	m_Parity = static_cast<QSerialPort::Parity>(settings.value(KEY_PARITY).toInt());
	m_FlowControl = static_cast<QSerialPort::FlowControl>(settings.value(KEY_FLOWCONTROL).toInt());
}

void SerialSettings::loadGeneric()
{
	m_StopBits = QSerialPort::StopBits::OneStop;
	m_DataBits = QSerialPort::DataBits::Data8;
	m_Parity = QSerialPort::Parity::NoParity;
	m_FlowControl = QSerialPort::FlowControl::NoFlowControl;
}

bool SerialSettings::isValid() {
	// Serial Port
	if (m_Port <= 0) {
		return false;
	}
	if (m_BaudRate == QAsyncSerialPort::BaudRate::BRUnknown) {
		return false;
	}
	if (m_StopBits == QSerialPort::StopBits::UnknownStopBits) {
		return false;
	}
	if (m_DataBits == QSerialPort::DataBits::UnknownDataBits) {
		return false;
	}
	if (m_Parity == QSerialPort::Parity::UnknownParity) {
		return false;
	}
	if (m_FlowControl == QSerialPort::FlowControl::UnknownFlowControl) {
		return false;
	}

	return true;
}

