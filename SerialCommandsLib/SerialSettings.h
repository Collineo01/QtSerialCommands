#pragma once

#include "serialcommandslib_global.h"

#include "QAsyncSerialPort.h"

/*! \class QSerialSettings
*
*	\brief Conteneur des paramètres d'un appareil de communication série. Permet la sauvegarde et le chargement de fichier ini.
*
*	save() pour sauvegarder et load() pour charger.
*
*/


class SerialSettings
{

public:
	SerialSettings(QAsyncSerialPort::BaudRate baudRate = QAsyncSerialPort::BaudRate::BR9600);
	SerialSettings(int port, QAsyncSerialPort::BaudRate baudRate = QAsyncSerialPort::BaudRate::BR9600);
	~SerialSettings();


	// Cles pour fichier INI
	static QString const KEY_PORT;
	static QString const KEY_BAUDRATE;
	static QString const KEY_STOPBITS;
	static QString const KEY_DATABITS;
	static QString const KEY_PARITY;
	static QString const KEY_FLOWCONTROL;

	// Serial Port
	int m_Port;
	QAsyncSerialPort::BaudRate m_BaudRate;
	QSerialPort::StopBits m_StopBits;
	QSerialPort::DataBits m_DataBits;
	QSerialPort::Parity m_Parity;
	QSerialPort::FlowControl m_FlowControl;

	void save(QString fileName);
	void load(QString fileName);
	void loadGeneric();

private:
	bool isValid();
};