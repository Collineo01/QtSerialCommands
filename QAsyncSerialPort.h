#pragma once


#include <QVector>
#include <QTimer>
#include <QSerialPort>

#include "qtserialcommands_global.h"
#include "SerialPortSettings.h"


/*! \class QAsyncSerialPort
*/

class QTSERIALCOMMANDS_EXPORT QAsyncSerialPort : public QSerialPort
{
	Q_OBJECT

public:
	static const int DEFAULT_TIMEOUT;

	QAsyncSerialPort(const SerialPortSettings & settings = SerialPortSettings());
	~QAsyncSerialPort();

	bool sendData(QString message);
	bool sendData(QByteArray data);

	SerialPortSettings getPortSettings() const { return m_portSettings; }
	int getPort() const { return m_portSettings.getPort(); }
	bool setPortSettings(const SerialPortSettings & settings, bool reconnect = true);
	bool setPort(unsigned int port, bool reconnect = true);
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
	void connectionUpdated(bool connected, bool failure = true);
	void messageSent();
	void updated(QString message);

protected:
	int m_timeout;

private:
	SerialPortSettings m_portSettings;
	QByteArray m_dataToSend;
	QTimer m_timer;
	qint64 m_nbOfBytesSent;

	QString createPortName(int port);
};
