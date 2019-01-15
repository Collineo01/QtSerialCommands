/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/

#pragma once


#include <QVector>
#include <QTimer>
#include <QSerialPort>

#include "qtserialcommands_global.h"


/*! \class QAsyncSerialPort
*
*	\brief Envoie et reçoit des données au getPort série.
*
*	Gère la connexion de l'appareil avec le getPort série (openPort() et closePort()).
*	Envoie des signaux par rapport aux erreurs de communication série.
*/

class SerialPortSettings;

class QTSERIALCOMMANDS_EXPORT QAsyncSerialPort : public QSerialPort
{
	Q_OBJECT

public:
	QAsyncSerialPort();
	~QAsyncSerialPort();

	enum class BaudRate {
		BR600 = 600, BR1200 = 1200, BR2400 = 2400, BR4800 = 4800, BR9600 = 9600, BR14400 = 14400, BR19200 = 19200, BR28800 = 28800, BR38400 = 38400, BR56000 = 56000, BR57600 = 57600,
		BR115200 = 115200, BR128000 = 128000, BR230400 = 230400, BR256000 = 256000, BRUnknown = -1
	};

	int m_timeout;

	bool sendMessage(QString message);
	bool sendMessage(QByteArray data);

public slots:
	bool openPort(SerialPortSettings * settings);
	virtual void closePort();

private slots:
	void readData();
	void handleTimeout();
	void handleBytesWritten(qint64 bytes);
	void handleError(QSerialPort::SerialPortError error);

signals:
	void dataRead(QByteArray data);
	//void responseRead(QString response);
	void connectionUpdated(bool connected, bool connectionFailed = false);
	void messageSent();
	void updated(QString message);

private:
	QString m_messageToSend;
	QTimer m_timer;
	qint64 m_NbOfBytesSent;

	QString createPortName(int port);
};
