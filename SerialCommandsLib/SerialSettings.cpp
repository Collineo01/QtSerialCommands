/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/

#include "SerialSettings.h"

#include <QSettings>
#include <QCoreApplication>

QString const SerialSettings::PORTNAME{ "portName" };
QString const SerialSettings::BAUDRATE{ "baudRate" };
QString const SerialSettings::STOPBITS{ "stopBits" };
QString const SerialSettings::DATABITS{ "dataBits" };
QString const SerialSettings::PARITY{ "parity" };
QString const SerialSettings::FLOWCONTROL{ "flowControl" };


SerialSettings::SerialSettings(QAsyncSerialPort::BaudRate baudRate)
	:
	mBaudRate{ baudRate }
{
	loadGeneric();
}

SerialSettings::SerialSettings(int comPort, QAsyncSerialPort::BaudRate baudRate)
	:
	mPortName{ "COM" + QString::number(comPort) },
	mBaudRate{ baudRate },
	mStopBits{ QSerialPort::StopBits::OneStop },
	mDataBits{ QSerialPort::DataBits::Data8 },
	mParity{ QSerialPort::Parity::NoParity },
	mFlowControl{ QSerialPort::FlowControl::NoFlowControl }
{

}

SerialSettings::~SerialSettings() {

}


void SerialSettings::save(QString fileName) {
	QSettings settings(fileName + ".ini", QSettings::Format::IniFormat);
	settings.setValue(PORTNAME, mPortName);
	settings.setValue(BAUDRATE, static_cast<int>(mBaudRate));
	settings.setValue(STOPBITS, mStopBits);
	settings.setValue(DATABITS, mDataBits);
	settings.setValue(PARITY, mParity);
	settings.setValue(FLOWCONTROL, mFlowControl);
}

void SerialSettings::load(QString fileName) {
	QSettings settings(fileName + ".ini", QSettings::Format::IniFormat);
	mPortName = settings.value(PORTNAME).toString();
	mBaudRate = static_cast<QAsyncSerialPort::BaudRate>(settings.value(BAUDRATE).toInt());
	mStopBits = static_cast<QSerialPort::StopBits>(settings.value(STOPBITS).toInt());
	mDataBits = static_cast<QSerialPort::DataBits>(settings.value(DATABITS).toInt());
	mParity = static_cast<QSerialPort::Parity>(settings.value(PARITY).toInt());
	mFlowControl = static_cast<QSerialPort::FlowControl>(settings.value(FLOWCONTROL).toInt());
}

void SerialSettings::loadGeneric()
{
	mStopBits = QSerialPort::StopBits::OneStop;
	mDataBits = QSerialPort::DataBits::Data8;
	mParity = QSerialPort::Parity::NoParity;
	mFlowControl = QSerialPort::FlowControl::NoFlowControl;
}

bool SerialSettings::isValid() {
	// Serial Port
	if (mPortName.isNull()) {
		return false;
	}
	if (mBaudRate == QAsyncSerialPort::BaudRate::BRUnknown) {
		return false;
	}
	if (mStopBits == QSerialPort::StopBits::UnknownStopBits) {
		return false;
	}
	if (mDataBits == QSerialPort::DataBits::UnknownDataBits) {
		return false;
	}
	if (mParity == QSerialPort::Parity::UnknownParity) {
		return false;
	}
	if (mFlowControl == QSerialPort::FlowControl::UnknownFlowControl) {
		return false;
	}

	return true;
}