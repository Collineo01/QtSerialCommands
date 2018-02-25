/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/

#pragma once


#include <QObject>
#include <QString>
#include <QList>
#include "QCommandSerialPort.h"
#include "SerialCommand.h"




class QSerialDevice : public QObject
{
	Q_OBJECT

public:
	QSerialDevice(QCommandSerialPort * sharedSerial = nullptr, SerialSettings * settings = nullptr, QObject *parent = nullptr);
	QSerialDevice(QMap<QString, SerialCommand const *> serialCommands, QMap<QString, QString> deviceMessages, 
					QCommandSerialPort * sharedSerial = nullptr, SerialSettings * settings = nullptr, QObject *parent = nullptr);
	~QSerialDevice();

	static QString const DEFAULT_INI;
	static QString const CURRENT_INI;
	static QString const TEMP_INI;
	static int const DEFAULT_COM_PORT;

	virtual void init(QString terminator);
	bool connectPort();
	bool connectPort(int port);
	void closePort();

	bool isConnected();

	void changePort(int port);

	void clearCommandAndResponseBuffers();

	int port() { return m_Port; }

	void setTimeout(int timeout);

protected:
	SerialSettings * m_PortSettings;
	QCommandSerialPort * m_Serial;
	QMap<QString, SerialCommand const *> m_SerialCommands;
	QMap<QString, QString> m_DeviceMessages;

	virtual void sendCommand(QString commandKey, QList<QVariant> args = QList<QVariant>());
	virtual void sendCommand(SerialCommand command, QList<QVariant> args = QList<QVariant>());
	virtual QByteArray sendBlockingCommand(QString commandKey, QList<QVariant> args = QList<QVariant>());

	virtual void fillDictionary() = 0;
	virtual void fillDeviceMessages() = 0;
	virtual void initDevice() = 0;

private:
	int m_Port;

	void initPortSettings();
	bool fileExists(QString fileName);


protected slots:
	virtual void handleMatchingResponse(QByteArray const &response, SerialCommand const &command) = 0;
	virtual void handleMessageReceived(QString const &message) = 0;
	virtual void handleConnectionUpdated(bool connected, bool connectionFailed = false);

private slots:
	void handleCommandTimedOut(QString command, QList<QVariant> args, int port);

signals:
	void responseMatchingCommandReceived(QByteArray const &response, SerialCommand const &command);
	void messageReceived(QString const &message);
	void connectionUpdated(bool connected, bool connectionFailed = false);
	void commandTimedOut(QString command, QList<QVariant> args, int port);
	void portTimedOut(int port);
};
