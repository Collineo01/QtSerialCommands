/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/

#include "QSerialDevice.h"
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include "SerialCommand.h"


QString const QSerialDevice::DEFAULT_INI{ "defaultPortSettings" };
QString const QSerialDevice::CURRENT_INI{ "currentPortSettings" };
QString const QSerialDevice::TEMP_INI{ "tempSettings" };

int const QSerialDevice::DEFAULT_COM_PORT{ 3 };


QSerialDevice::QSerialDevice(QCommandSerialPort * sharedSerial, SerialSettings * settings, QObject *parent)
	:
	QObject(parent),
	mPortSettings{ settings }, // TODO : remplacer par une instance au lieu d'un pointeur (doit créer le copy constructor)
	mSerial{ sharedSerial }
{
	if (sharedSerial == nullptr)
	{
		mSerial = new QCommandSerialPort;
	}
	if (settings == nullptr)
	{
		mPortSettings = new SerialSettings(DEFAULT_COM_PORT);
	}

	connect(mSerial, &QCommandSerialPort::responseMatchesCommand, this, &QSerialDevice::handleMatchingResponse);
	connect(mSerial, &QCommandSerialPort::messageReceived, this, &QSerialDevice::handleMessageReceived);
	connect(mSerial, &QAsyncSerialPort::connectionUpdated, this, &QSerialDevice::handleConnectionUpdated);

	// Initialiser les paramètres de connexion série
	initPortSettings();
}

QSerialDevice::~QSerialDevice()
{
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Slots
///////////////////////////////////////////////////////////////////////////////////////////////

void QSerialDevice::handleConnectionUpdated(bool connected)
{
	mIsConnected = connected;

	if (connected)
	{
		initDevice();
		qDebug() << "Connection successful on " + mPortSettings->mPortName;
	}
	else
	{
		qDebug() << "Connection failed on " + mPortSettings->mPortName;
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////////////////////

QByteArray QSerialDevice::sendBlockingCommand(QString command, QList<QVariant> params)
{
	SerialCommand cmd = *mSerialCommands[command];
	return mSerial->sendBlockingCommand(cmd, params);
}

void QSerialDevice::sendCommand(QString command, QList<QVariant> params)
{
	mSerial->setDevelopmentMode(false);
	QPair<SerialCommand const &, QList<QVariant>> commandAndParams(*mSerialCommands[command], params);
	mSerial->writeToBuffer(commandAndParams);
}

void QSerialDevice::init()
{
	// Remplir le dictionnaire de commandes
	fillDictionary();

	// Remplir le dictionnaire de messages
	fillDeviceMessages();
}

void QSerialDevice::changeComPort(int comPort)
{
	mSerial->closeSerialPort();
	mPortSettings->mPortName = "COM" + QString::number(comPort);
	connectComPort();
}

void QSerialDevice::connectComPort()
{
	mSerial->openSerialPort(mPortSettings->mPortName, mPortSettings->mBaudRate, mPortSettings->mDataBits, mPortSettings->mParity, mPortSettings->mStopBits, mPortSettings->mFlowControl);
}

bool QSerialDevice::portIsOpened()
{
	return mSerial->isOpen();
}

/*! Affectation de mSettings à partir d'un fichier ini sauvegardé. Si aucun n'est sauvegardé, c'est ici qu'on en crée un avec des paramètres par défaut.
*/
void QSerialDevice::initPortSettings()
{
	// Fichier avec parametres modifies existant (ATTENTION : Si le fichier existe déjà, il utilisera le QSerialSettings contenu avant celui passé dans le constructeur)
	if (fileExists(CURRENT_INI))
	{
		mPortSettings->load(CURRENT_INI);
	}
	// Si un QSerialSetings est passé au constructeur
	else if (mPortSettings != nullptr)
	{
		mPortSettings->save(CURRENT_INI);
	}
	else
	{
		// Default Settings
		mPortSettings = new SerialSettings(DEFAULT_COM_PORT);

		// Sauvegarde du default si non existant
		if (!fileExists(DEFAULT_INI))
		{
			mPortSettings->save(DEFAULT_INI);
		}
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Helper Methods
///////////////////////////////////////////////////////////////////////////////////////////////

bool QSerialDevice::fileExists(QString fileName)
{
	QFileInfo check_file(QDir::currentPath() + "/" + fileName + ".ini");
	return (check_file.exists() && check_file.isFile());
}
