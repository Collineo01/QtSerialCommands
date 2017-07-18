#pragma once

#include "serialcommandslib_global.h"

#include <QObject>
#include <QMap>
#include <QString>
#include <QList>
#include <QVariant>
#include "QCommandSerialPort.h"
#include "SerialSettings.h"


class SERIALCOMMANDSLIB_EXPORT QSerialDevice : public QObject
{
	Q_OBJECT

public:
	QSerialDevice(QCommandSerialPort * sharedSerial = nullptr, SerialSettings * settings = nullptr, QObject *parent = nullptr);
	~QSerialDevice();

	static QString const DEFAULT_INI;
	static QString const CURRENT_INI;
	static QString const TEMP_INI;
	static int const DEFAULT_COM_PORT;

	// enum class Command { }; // Coquille vide. Ce enum doit être défini dans la classe enfant

	// virtual void sendCommand(Command command, QList<QVariant> params = QList<QVariant>()) = 0; // doit être redéfini telle que ci dessous pour utiliser le enum Command de la classe enfant

	//void QSerialDevice::sendCommand(Command command, QList<QVariant> params) 
	//{
	//	mSerial.setDevelopmentMode(false);
	//	QPair<QSerialCommand const &, QList<QVariant>> commandAndParams(*mSerialCommands[command], params);
	//	mSerial.writeToBuffer(commandAndParams);
	//}

	virtual void init();

	bool isConnected() { return mIsConnected; }

	void changeComPort(int comPort);

	bool portIsOpened();


protected:
	SerialSettings * mPortSettings;
	QCommandSerialPort * mSerial;
	QMap<QString, SerialCommand const *> mSerialCommands;
	QMap<QString, QString> mDeviceMessages;

	bool mIsConnected;

	void sendCommand(QString command, QList<QVariant> params = QList<QVariant>());
	QByteArray sendBlockingCommand(QString command, QList<QVariant> params = QList<QVariant>());

	virtual void fillDictionary() = 0;
	virtual void fillDeviceMessages() = 0;
	virtual void initDevice() = 0;

private:
	void initPortSettings();
	bool fileExists(QString fileName);


	protected slots:
	virtual void handleMatchingResponse(QByteArray const &response, SerialCommand const &command) = 0;
	virtual void handleMessageReceived(QString const &message) = 0;
	virtual void handleConnectionUpdated(bool connected);
};
