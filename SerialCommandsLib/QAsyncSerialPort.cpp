/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/


#include "QAsyncSerialPort.h"
//#include <QDebug>
#include <QCoreApplication>
#include <QTime>
#include <QSettings>
#include <QDebug>


////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////////////////////////////////////////

QAsyncSerialPort::QAsyncSerialPort() :
	m_Timeout{ 5000 }
{
	//openSerialPort();
	mTimer.setSingleShot(true);

	connect(this, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error), this, &QAsyncSerialPort::handleError);
	connect(this, &QSerialPort::readyRead, this, &QAsyncSerialPort::readData);
	connect(&mTimer, &QTimer::timeout, this, &QAsyncSerialPort::handleTimeout);
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////////////////////

bool QAsyncSerialPort::sendMessage(QString message) {
	mMessageToWrite = message;
	QByteArray data = mMessageToWrite.toLatin1();
	return sendMessage(data);
}

bool QAsyncSerialPort::sendMessage(QByteArray data)
{
	bool success = false;

	if (isOpen()) 
	{
		qint64 bytesWritten = write(data);
		if (bytesWritten == -1) {
			emit updated(QObject::tr("Failed to write the data to port %1, error: %2").arg(portName()).arg(errorString()));
			//QCoreApplication::exit(1);
			success = false;
		}
		else if (bytesWritten != data.size()) {
			emit updated(QObject::tr("Failed to write all the data to port %1, error: %2").arg(portName()).arg(errorString()));
			//QCoreApplication::exit(1);
			success = false;
		}
		else {
			emit messageSent();
			if (!mTimer.isActive()) {
				mTimer.start(m_Timeout);
			}
			success = true;
		}
	}

	return success;
}

void QAsyncSerialPort::handleBytesWritten(qint64 bytes)
{
	mBytesWritten += bytes;
	if (mBytesWritten == mMessageToWrite.size()) {
		mBytesWritten = 0;
		emit updated(QObject::tr("Data successfully sent to port %1").arg(portName()));
	}
	mTimer.stop();
}

void QAsyncSerialPort::handleTimeout()
{
	emit updated(QObject::tr("Operation timed out for port %1, error: %2").arg(portName()).arg(errorString()));
}

void QAsyncSerialPort::handleError(QSerialPort::SerialPortError serialPortError)
{
	if (serialPortError == QSerialPort::WriteError) {
		emit updated(QObject::tr("An I/O error occurred while writing the data to port %1, error: %2").arg(portName()).arg(errorString()));
		mTimer.stop();
	}
}

void QAsyncSerialPort::readData() {
	mTimer.stop();
	QByteArray data = readAll();
	QString response(data);
	emit dataRead(data);
}

bool QAsyncSerialPort::openSerialPort(QString portName, BaudRate baudRate, QSerialPort::DataBits dataBits, QSerialPort::Parity parity, QSerialPort::StopBits stopBits, QSerialPort::FlowControl flowControl)
{
	bool success = false;

	setPortName(portName);
	if (!setBaudRate(static_cast<int>(baudRate))) {
		emit updated("Failed to set BaudRate");
		//qDebug() << errorString();
	}
	if (!setDataBits(dataBits)) {
		emit updated("Failed to set DataBits");
		//qDebug() << errorString();
	}
	if (!setParity(parity)) {
		emit updated("Failed to set Parity");
		//qDebug() << errorString();
	}
	if (!setStopBits(stopBits)) {
		emit updated("Failed to set StopBits");
		//qDebug() << errorString();
	}
	if (!setFlowControl(flowControl)) {
		emit updated("Failed to set FlowControl");
		//qDebug() << errorString();
	}
	if (open(QIODevice::ReadWrite)) {
		//qDebug() << "Connected to the device for writing and reading!";
		emit updated("Connected to the device for writing and reading!");
		success = true;
	}
	else {
		//qDebug() << "Unable to connect to the device for writing and reading!";
		emit updated("Unable to connect to the device for writing and reading!");
	}
	emit connectionUpdated(success, !success);

	return success;
}

void QAsyncSerialPort::closeSerialPort()
{
	if (isOpen()) {
		close();
		emit connectionUpdated(false);
		emit updated("Disconnected");
		//qDebug() << "Disconnected";
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
///////////////////////////////////////////////////////////////////////////////////////////////

QAsyncSerialPort::~QAsyncSerialPort()
{

}



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
