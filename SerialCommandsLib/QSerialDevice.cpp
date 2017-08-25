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
	mPortSettings{ settings }, // TODO : remplacer par une instance au lieu d'un pointeur (doit cr�er le copy constructor)
	mSerial{ sharedSerial },
	m_Port{ -1 }
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

	// Initialiser les param�tres de connexion s�rie
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
	bool connected = true;

	if (m_Port != -1 && !portIsOpened()) {
		changeComPort(m_Port);
		connected = connectComPort();
	}

	if (connected)
	{
		SerialCommand cmd = *mSerialCommands[command];
		QByteArray response = mSerial->sendBlockingCommand(cmd, params);
		//qDebug() << "BlockingResponse : " << response;
		return response;
	}
	else
	{
		qDebug() << "Connection failed on " + mSerial->portName();
		return QByteArray();
	}
}

void QSerialDevice::sendCommand(QString command, QList<QVariant> params)
{
	bool connected = true;

	if (m_Port != -1 && !portIsOpened()) {
		changeComPort(m_Port);
		connected = connectComPort();
	}

	if (connected)
	{
		mSerial->setDevelopmentMode(false);
		QPair<SerialCommand const &, QList<QVariant>> commandAndParams(*mSerialCommands[command], params);
		mSerial->writeToBuffer(commandAndParams);
	}
	else
	{
		qDebug() << "Connection failed on " + mSerial->portName();
	}
}

void QSerialDevice::init(QString terminator)
{
	// Remplir le dictionnaire de commandes
	fillDictionary();

	// Remplir le dictionnaire de messages
	fillDeviceMessages();

	// Messages que peut envoyer l'appareil (cl�s du dictionnaire de messages)
	mSerial->setDeviceMessages(mDeviceMessages.keys(), terminator);
}

void QSerialDevice::changeComPort(int comPort)
{
	mPortSettings->mPortName = "COM" + QString::number(comPort);
	mSerial->changeSerialSettings(mPortSettings);
}

bool QSerialDevice::connectComPort()
{
	if (!portIsOpened()) {
		return mSerial->openSerialPort(mPortSettings->mPortName, mPortSettings->mBaudRate, mPortSettings->mDataBits, mPortSettings->mParity, mPortSettings->mStopBits, mPortSettings->mFlowControl);
	}
	return true;
}

void QSerialDevice::closeComPort()
{
	mSerial->closeSerialPort();
}

bool QSerialDevice::portIsOpened()
{
	return mSerial->isOpen();
}

/*! Affectation de mSettings � partir d'un fichier ini sauvegard�. Si aucun n'est sauvegard�, c'est ici qu'on en cr�e un avec des param�tres par d�faut.
*/
void QSerialDevice::initPortSettings()
{
	// Fichier avec parametres modifies existant (ATTENTION : Si le fichier existe d�j�, il utilisera le QSerialSettings contenu avant celui pass� dans le constructeur)
	if (fileExists(CURRENT_INI))
	{
		mPortSettings->load(CURRENT_INI);
	}
	// Si un QSerialSetings est pass� au constructeur
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