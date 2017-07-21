/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/

/*! \class QSerialSettings
*
*	\brief Conteneur des paramètres d'un appareil de communication série. Permet la sauvegarde et le chargement de fichier ini.
*
*	save() pour sauvegarder et load() pour charger.
*
*/


#ifndef Q_SERIALSETTINGS_H
#define Q_SERIALSETTINGS_H



#include <QString>
#include "QAsyncSerialPort.h"

class SerialSettings
{

public:
	SerialSettings(QAsyncSerialPort::BaudRate baudRate = QAsyncSerialPort::BaudRate::BR9600);
	SerialSettings(int comPort, QAsyncSerialPort::BaudRate baudRate = QAsyncSerialPort::BaudRate::BR9600);
	~SerialSettings();


	// Cles pour fichier INI
	static QString const PORTNAME;
	static QString const BAUDRATE;
	static QString const STOPBITS;
	static QString const DATABITS;
	static QString const PARITY;
	static QString const FLOWCONTROL;

	// Serial Port
	QString mPortName;
	QAsyncSerialPort::BaudRate mBaudRate;
	QSerialPort::StopBits mStopBits;
	QSerialPort::DataBits mDataBits;
	QSerialPort::Parity mParity;
	QSerialPort::FlowControl mFlowControl;


	void save(QString fileName);
	void load(QString fileName);
	void loadGeneric();

private:
	bool isValid();
};
#endif //Q_SERIALSETTINGS_H
