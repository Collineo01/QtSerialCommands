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
	connect(mSerial, &QCommandSerialPort::commandTimeout, this, &QSerialDevice::commandTimeout);

	// Initialiser les paramètres de connexion série
	//initPortSettings();
}

QSerialDevice::~QSerialDevice()
{
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Slots
///////////////////////////////////////////////////////////////////////////////////////////////

void QSerialDevice::handleConnectionUpdated(bool connected, bool connectionFailed)
{
	mIsConnected = connected;

	if (connected)
	{
		initDevice();
		qDebug() << "Connection successful on " + mSerial->portName();
	}
	else if (connectionFailed)
	{
		qDebug() << "Connection failed on " + mSerial->portName();
	}
	else
	{
		qDebug() << "Connection closed on " + mSerial->portName();
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

void QSerialDevice::init(QString terminator)
{
	// Remplir le dictionnaire de commandes
	fillDictionary();

	// Remplir le dictionnaire de messages
	fillDeviceMessages();

	// Messages que peut envoyer l'appareil (clés du dictionnaire de messages)
	mSerial->setDeviceMessages(mDeviceMessages.keys(), terminator);
}

void QSerialDevice::changeComPort(int comPort)
{
	mPortSettings->mPortName = "COM" + QString::number(comPort);
	mSerial->changeSerialSettings(mPortSettings);
}

bool QSerialDevice::connectComPort()
{
	return mSerial->openSerialPort(mPortSettings->mPortName, mPortSettings->mBaudRate, mPortSettings->mDataBits, mPortSettings->mParity, mPortSettings->mStopBits, mPortSettings->mFlowControl);
}

void QSerialDevice::closeComPort()
{
	mSerial->closeSerialPort();
}

bool QSerialDevice::portIsOpened()
{
	qDebug() << "test";
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