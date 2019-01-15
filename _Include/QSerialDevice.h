/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/

#pragma once


#include <QObject>
#include <QString>
#include <QList>

#include "QSmartSerialPort.h"
#include "SerialCommand.h"
#include "SerialCommandFactory.h"
#include "SerialMessageFactory.h"


class QSerialDevice : public QObject
{
	Q_OBJECT

public:
	QSerialDevice(
		const SerialCommandFactory & commandFactory,
		const SerialMessageFactory & messageFactory,
		SerialPortSettings * settings = nullptr,
		QSmartSerialPort * sharedSerial = nullptr,
		QObject *parent = nullptr
	);
	QSerialDevice(
		const SerialCommandFactory & commandFactory,
		SerialPortSettings * settings = nullptr,
		QSmartSerialPort * sharedSerial = nullptr,
		QObject *parent = nullptr
	);
	~QSerialDevice();

	static QString const DEFAULT_INI;
	static QString const CURRENT_INI;
	static QString const TEMP_INI;
	static int const DEFAULT_PORT;

	virtual void init(QString terminator);
	bool connectPort();
	bool connectPort(int port);
	void closePort();

	bool isConnected();

	void changePort(int port);

	int getPort() { return m_portSettings->getPort(); }

	void setTimeout(int timeout);

protected:
	SerialPortSettings * m_portSettings;
	QSmartSerialPort * m_serialPort;
	QMap<QString, const SerialCommand *> m_serialCommands;
	SerialMessages m_deviceMessages;

	void sendCommand(const QString & commandKey, QList<SerialCommandArg> args = QList<SerialCommandArg>());
	QByteArray sendBlockingCommand(const QString & commandKey, QList<SerialCommandArg> args = QList<SerialCommandArg>());

	virtual void initDevice() = 0;

private:
	void initPortSettings();
	bool fileExists(QString fileName);

protected slots:
	virtual void handleMatchingResponse(QByteArray const &response, SerialCommand const &command) = 0;
	virtual void handleMessageReceived(QString const &message) = 0;
	virtual void handleConnectionUpdated(bool connected, bool connectionFailed = false);

private slots:
	void handleCommandTimedOut(QString commandKey, QList<SerialCommandArg> args, int port);

signals:
	void responseMatchingCommandReceived(QByteArray const &response, SerialCommand const &command);
	void messageReceived(QString const &message);
	void connectionUpdated(bool connected, bool connectionFailed = false);
	void commandTimedOut(QString command, QList<SerialCommandArg> args, int port);
	void portTimedOut(int port);
};
