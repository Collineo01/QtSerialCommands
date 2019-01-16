#pragma once


#include <QVector>
#include <QTimer>
#include <QSerialPort>

#include "qtserialcommands_global.h"
#include "SerialPortSettings.h"


/*! \class QAsyncSerialPort
*
*	\brief Envoie et reçoit des données au getPort série.
*
*	Gère la connexion de l'appareil avec le getPort série (openPort() et closePort()).
*	Envoie des signaux par rapport aux erreurs de communication série.
*/

class QTSERIALCOMMANDS_EXPORT QAsyncSerialPort : public QSerialPort
{
	Q_OBJECT

public:
	QAsyncSerialPort(const SerialPortSettings & settings = SerialPortSettings());
	~QAsyncSerialPort();

	bool sendMessage(QString message);
	bool sendMessage(QByteArray data);

	SerialPortSettings getPortSettings() const { return m_portSettings; }
	int getPort() const { return m_portSettings.getPort(); }
	bool setPortSettings(const SerialPortSettings & settings);
	bool setPort(unsigned int port);
	void setTimeout(unsigned int timeoutMs) { m_timeout = timeoutMs; }

public slots:
	bool openPort();
	virtual void closePort();

private slots:
	void readData();
	void handleTimeout();
	void handleBytesWritten(qint64 bytes);
	void handleError(SerialPortError error);

signals:
	void dataRead(QByteArray data);
	//void responseRead(QString response);
	void connectionUpdated(bool connected, bool connectionFailed = false);
	void messageSent();
	void updated(QString message);

protected:
	int m_timeout;

private:
	SerialPortSettings m_portSettings;
	QString m_messageToSend;
	QTimer m_timer;
	qint64 m_nbOfBytesSent;

	QString createPortName(int port);
};
