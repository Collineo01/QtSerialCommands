#pragma once

#include "qtserialcommands_global.h"

#include <QObject>
#include <QString>
#include <QList>

#include "QMatchSerialPort.h"
#include "SerialCommand.h"
#include "SerialCommandFactory.h"
#include "SerialMessageFactory.h"


class QTSERIALCOMMANDS_EXPORT QSerialDevice : public QObject
{
	Q_OBJECT

public:
	QSerialDevice(
		QMatchSerialPort & serialPort,
		const SerialCommandFactory & commandFactory,
		const SerialMessageFactory & messageFactory,
		QObject *parent = nullptr
	);
	QSerialDevice(
		QMatchSerialPort & serialPort,
		const SerialCommandFactory & commandFactory,
		QObject *parent = nullptr
	);
	~QSerialDevice();

	virtual void sendCommand(const QString & commandKey, QList<SerialCommandArg> args = QList<SerialCommandArg>());
	virtual QByteArray sendCommandAwait(const QString & commandKey, QList<SerialCommandArg> args = QList<SerialCommandArg>());

	bool connectPort();
	bool connectPort(int port);
	void closePort();

	bool isConnected();

	void setPort(unsigned int port) { m_serialPort.setPort(port); }
	int getPort() const { return m_serialPort.getPort(); }

protected:
	QMatchSerialPort & m_serialPort;
	QMap<QString, const SerialCommand *> m_serialCommands;
	SerialMessages m_expectedMessages;

	virtual void initDevice() = 0;

protected slots:
	virtual void handleMatchingResponse(const QByteArray & response, SerialCommand command) = 0;
	virtual void handleMessageReceived(const QByteArray & message, const QString & description) = 0;
	virtual void handleConnectionUpdated(bool connected, bool connectionFailed = false);

private slots:
	void handleCommandTimedOut(QString commandKey, QList<SerialCommandArg> args, int port);

signals:
	void responseMatchingCommandReceived(const QByteArray & response, const SerialCommand & command);
	void messageReceived(const QByteArray & message, const QString & description);
	void connectionUpdated(bool connected, bool connectionFailed = false);
	void commandTimedOut(QString command, QList<SerialCommandArg> args, int port);
	void portTimedOut(int port);
};
