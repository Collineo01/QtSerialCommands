/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/

#pragma once

#include <QSerialDevice.h>



class QSerialDevicePort : public QSerialDevice
{
	Q_OBJECT

public:
	QSerialDevicePort(QMap<QString, SerialCommand const *> serialCommands, QMap<QString, QString> deviceMessages,
						QCommandSerialPort * sharedSerial = nullptr, SerialSettings * settings = nullptr, QObject *parent = nullptr);
	~QSerialDevicePort();

	void sendCommand(QString commandKey, QList<QVariant> args = QList<QVariant>());
	void sendCommand(SerialCommand command, QList<QVariant> args = QList<QVariant>());
	QByteArray sendBlockingCommand(QString commandKey, QList<QVariant> args = QList<QVariant>());

	void fillDictionary() override {}
	void fillDeviceMessages() override {}
	void initDevice() override {}

private slots:
	void handleMatchingResponse(QByteArray const &response, SerialCommand const &command){};
	void handleMessageReceived(QString const &message){};
};
