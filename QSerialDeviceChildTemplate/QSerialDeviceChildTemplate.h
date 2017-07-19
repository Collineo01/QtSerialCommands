#pragma once

#ifdef _DEBUG
#pragma comment(lib, "SerialCommandsLibd.lib")
#else
#pragma comment(lib, "SerialCommandsLib.lib")
#endif

#include <...>
#include "QSerialDevice.h"



class Q_BME280 : public QSerialDevice
{
	Q_OBJECT

public:
	Q_BME280(QCommandSerialPort * sharedSerial = nullptr, SerialSettings * settings = nullptr, QObject * parent = nullptr);
	~Q_BME280();

	static const QString CMD_GET_TEMPERATURE;
	static const QString CMD_GET_PRESSURE;
	static const QString CMD_GET_HUMIDITY;
	
	// Méthodes propres à l'appareil (avec paramètre(s))

private:
	void fillDictionary();
	void fillDeviceMessages();
	void initDevice();

private slots :
	void handleMatchingResponse(QByteArray const &response, SerialCommand const &command);
	void handleMessageReceived(QString const &message);
};