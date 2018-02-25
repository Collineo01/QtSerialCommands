/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/

#include "QSerialDevicePort.h"

QSerialDevicePort::QSerialDevicePort(QMap<QString, SerialCommand const *> serialCommands, QMap<QString, QString> deviceMessages,
										QCommandSerialPort * sharedSerial, SerialSettings * settings, QObject *parent)
	: QSerialDevice(serialCommands, deviceMessages, sharedSerial, settings, parent)
{
}

QSerialDevicePort::~QSerialDevicePort()
{
}

void QSerialDevicePort::sendCommand(QString commandKey, QList<QVariant> args)
{
	QSerialDevice::sendCommand(commandKey, args);
}

void QSerialDevicePort::sendCommand(SerialCommand command, QList<QVariant> args)
{
	QSerialDevice::sendCommand(command, args);
}

QByteArray QSerialDevicePort::sendBlockingCommand(QString commandKey, QList<QVariant> args)
{
	return QSerialDevice::sendBlockingCommand(commandKey, args);
}
