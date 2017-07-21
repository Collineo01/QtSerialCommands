/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/


#include "QAsyncSerialPort.h"
//#include <QDebug>
#include <QCoreApplication>
#include <QTime>


////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////////////////////////////////////////

QAsyncSerialPort::QAsyncSerialPort()
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

void QAsyncSerialPort::sendMessage(QString message) {
	mMessageToWrite = message;
	QByteArray data = mMessageToWrite.toLatin1();
	sendMessage(data);
}

void QAsyncSerialPort::sendMessage(QByteArray data) {
	if (isOpen()) {
		qint64 bytesWritten = write(data);
		if (bytesWritten == -1) {
			emit updated(QObject::tr("Failed to write the data to port %1, error: %2").arg(portName()).arg(errorString()));
			//QCoreApplication::exit(1);
		}
		else if (bytesWritten != data.size()) {
			emit updated(QObject::tr("Failed to write all the data to port %1, error: %2").arg(portName()).arg(errorString()));
			//QCoreApplication::exit(1);
		}
		else {
			emit messageSent();
			if (!mTimer.isActive()) {
				mTimer.start(5000);
			}
		}
	}
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
