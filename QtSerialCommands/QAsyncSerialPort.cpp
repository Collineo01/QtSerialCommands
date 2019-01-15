/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/


#include "QAsyncSerialPort.h"
#include <QCoreApplication>
#include <QTime>
#include <QDebug>
#include "SerialPortSettings.h"


////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////////////////////////////////////////

QAsyncSerialPort::QAsyncSerialPort() :
	m_timeout{ 5000 }
{
	m_timer.setSingleShot(true);

	connect(this, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error), this, &QAsyncSerialPort::handleError);
	connect(this, &QSerialPort::readyRead, this, &QAsyncSerialPort::readData);
	connect(&m_timer, &QTimer::timeout, this, &QAsyncSerialPort::handleTimeout);
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////////////////////

bool QAsyncSerialPort::sendMessage(QString message) {
	m_messageToSend = message;
	QByteArray data = m_messageToSend.toLatin1();
	return sendMessage(data);
}

bool QAsyncSerialPort::sendMessage(QByteArray data)
{
	bool success = false;

	if (isOpen())
	{
		qint64 bytesWritten = write(data);
		if (bytesWritten == -1) {
			emit updated(QObject::tr("Failed to writeCommand the data to getPort %1, error: %2").arg(portName()).arg(errorString()));
			//QCoreApplication::exit(1);
			success = false;
		}
		else if (bytesWritten != data.size()) {
			emit updated(QObject::tr("Failed to writeCommand all the data to getPort %1, error: %2").arg(portName()).arg(errorString()));
			//QCoreApplication::exit(1);
			success = false;
		}
		else {
			emit messageSent();
			if (!m_timer.isActive()) {
				m_timer.start(m_timeout);
			}
			success = true;
		}
	}

	return success;
}

void QAsyncSerialPort::handleBytesWritten(qint64 bytes)
{
	m_NbOfBytesSent += bytes;
	if (m_NbOfBytesSent == m_messageToSend.size()) {
		m_NbOfBytesSent = 0;
		emit updated(QObject::tr("Data successfully sent to getPort %1").arg(portName()));
	}
	m_timer.stop();
}

void QAsyncSerialPort::handleTimeout()
{
	emit updated(QObject::tr("Operation timed out for getPort %1, error: %2").arg(portName()).arg(errorString()));
}

void QAsyncSerialPort::handleError(QSerialPort::SerialPortError serialPortError)
{
	if (serialPortError == QSerialPort::WriteError) {
		emit updated(QObject::tr("An I/O error occurred while writing the data to getPort %1, error: %2").arg(portName()).arg(errorString()));
		m_timer.stop();
	}
}

void QAsyncSerialPort::readData() {
	m_timer.stop();
	QByteArray data = readAll();
	QString response(data);
	emit dataRead(data);
}

QString QAsyncSerialPort::createPortName(int port)
{
	return "COM" + QString::number(port);
}

bool QAsyncSerialPort::openPort(SerialPortSettings * settings)
{
	bool success = false;

	QString portName = createPortName(settings->getPort());
	setPortName(portName);

	if (!setBaudRate(static_cast<int>(settings->getBaudRate()))) {
		emit updated("Failed to set BaudRate");
	}
	if (!setDataBits(settings->getDataBits())) {
		emit updated("Failed to set DataBits");
	}
	if (!setParity(settings->getParity())) {
		emit updated("Failed to set Parity");
	}
	if (!setStopBits(settings->getStopBits())) {
		emit updated("Failed to set StopBits");
	}
	if (!setFlowControl(settings->getFlowControl())) {
		emit updated("Failed to set FlowControl");
	}
	if (open(QIODevice::ReadWrite)) {
		emit updated("Connected to the device for writing and reading!");
		success = true;
	}
	else {
		emit updated("Unable to connect to the device for writing and reading!");
	}
	emit connectionUpdated(success, !success);

	return success;
}

void QAsyncSerialPort::closePort()
{
	if (isOpen()) {
		close();
		emit connectionUpdated(false);
		emit updated("Disconnected");
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
///////////////////////////////////////////////////////////////////////////////////////////////

QAsyncSerialPort::~QAsyncSerialPort()
{

}