#include "QSerialDevice.h"

#include <QDebug>
#include <QDir>

#include "SerialCommand.h"


QSerialDevice::QSerialDevice(
	QMatchSerialPort & serialPort,
	const SerialCommandFactory & commandFactory,
	const SerialMessageFactory & messageFactory,
	QObject * parent
) :
	QObject(parent),
	m_serialPort{ serialPort },
	m_serialCommands{ commandFactory.createSerialCommands() },
	m_expectedMessages{ messageFactory.createSerialMessages() }
{
	connect(&m_serialPort, &QMatchSerialPort::matchingResponseReceived, this, &QSerialDevice::handleMatchingResponse);
	connect(&m_serialPort, &QMatchSerialPort::messageReceived, this, &QSerialDevice::handleMessageReceived);
	connect(&m_serialPort, &QAsyncSerialPort::connectionUpdated, this, &QSerialDevice::handleConnectionUpdated);
	connect(&m_serialPort, &QAsyncSerialPort::connectionUpdated, this, &QSerialDevice::connectionUpdated);
	connect(&m_serialPort, &QMatchSerialPort::commandTimedOut, this, &QSerialDevice::commandTimedOut);
	connect(&m_serialPort, &QMatchSerialPort::commandTimedOut, this, &QSerialDevice::handleCommandTimedOut);
}

QSerialDevice::QSerialDevice(
	QMatchSerialPort & serialPort,
	const SerialCommandFactory & commandFactory,
	QObject * parent
) :
	QSerialDevice(serialPort, commandFactory, DummySerialMessageFactory(), parent)
{
}

QSerialDevice::~QSerialDevice()
{
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Slots
///////////////////////////////////////////////////////////////////////////////////////////////

void QSerialDevice::handleConnectionUpdated(bool connected, bool failure)
{
	if (connected)
	{
		qDebug() << "Connection successful on " + m_serialPort.portName();
	}
	else if (failure)
	{
		qDebug() << "Connection failed on " + m_serialPort.portName();
	}
	else
	{
		qDebug() << "Connection closed on " + m_serialPort.portName();
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////////////////////

void QSerialDevice::sendCommand(const QString & commandKey, QList<SerialCommandArg> args)
{
	m_serialPort.sendCommand(*m_serialCommands[commandKey], args);
}

QByteArray QSerialDevice::sendCommandAwait(const QString & commandKey, QList<SerialCommandArg> args)
{
	return m_serialPort.sendCommandAwait(*m_serialCommands[commandKey], args);
}

bool QSerialDevice::connectPort()
{
	if (!isConnected())
	{
		return m_serialPort.openPort();
	}
	return true;
}

bool QSerialDevice::connectPort(int port)
{
	setPort(port);
	bool connected = connectPort();

	return connected;
}

void QSerialDevice::closePort()
{
	m_serialPort.closePort();
}

bool QSerialDevice::isConnected()
{
	return m_serialPort.isOpen();
}

void QSerialDevice::handleCommandTimedOut(QString commandKey, QList<SerialCommandArg> args, int port)
{
	emit portTimedOut(port);
}