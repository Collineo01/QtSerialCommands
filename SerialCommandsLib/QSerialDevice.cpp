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
	m_Serial{ sharedSerial },
	m_Port{ -1 }
{
	if (sharedSerial == nullptr)
	{
		m_Serial = new QCommandSerialPort;
	}
	if (settings == nullptr)
	{
		mPortSettings = new SerialSettings(DEFAULT_COM_PORT);
	}

	connect(m_Serial, &QCommandSerialPort::responseMatchesCommand, this, &QSerialDevice::handleMatchingResponse);
	connect(m_Serial, &QCommandSerialPort::messageReceived, this, &QSerialDevice::handleMessageReceived);
	connect(m_Serial, &QAsyncSerialPort::connectionUpdated, this, &QSerialDevice::handleConnectionUpdated);

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
		qDebug() << "Connection successful on " + m_Serial->portName();
	}
	else if (connectionFailed)
	{
		qDebug() << "Connection failed on " + m_Serial->portName();
	}
	else
	{
		qDebug() << "Connection closed on " + m_Serial->portName();
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////////////////////

void QSerialDevice::sendCommand(SerialCommand command, QList<QVariant> params)
{
	bool connected = true;

	if (m_Port != -1 && !portIsOpened()) {
		changeComPort(m_Port);
		connected = connectComPort();
	}

	if (connected)
	{
		m_Serial->setDevelopmentMode(false);
		/*QPair<SerialCommand const &, QList<QVariant>> commandAndParams(command, params);
		m_Serial->writeToBuffer(commandAndParams);*/
		command.setParameters(params);
		emit m_Serial->sendCommandRequest(command);
	}
	else
	{
		qDebug() << "Connection failed on " + m_Serial->portName();
	}
}

void QSerialDevice::sendCommand(QString commandKey, QList<QVariant> params)
{
	SerialCommand command = *mSerialCommands[commandKey];
	sendCommand(command, params);
}

QByteArray QSerialDevice::sendBlockingCommand(QString commandKey, QList<QVariant> params)
{
	bool connected = true;

	if (m_Port != -1 && !portIsOpened()) {
		changeComPort(m_Port);
		connected = connectComPort();
	}

	if (connected)
	{
		SerialCommand cmd = *mSerialCommands[commandKey];
		QByteArray response = m_Serial->sendBlockingCommand(cmd, params);
		//qDebug() << "BlockingResponse : " << response;
		return response;
	}
	else
	{
		qDebug() << "Connection failed on " + m_Serial->portName();
		return QByteArray();
	}
}

void QSerialDevice::init(QString terminator)
{
	// Remplir le dictionnaire de commandes
	fillDictionary();

	// Remplir le dictionnaire de messages
	fillDeviceMessages();

	// Messages que peut envoyer l'appareil (clés du dictionnaire de messages)
	m_Serial->setDeviceMessages(mDeviceMessages.keys(), terminator);
}

void QSerialDevice::changeComPort(int comPort)
{
	mPortSettings->mPortName = "COM" + QString::number(comPort);
	m_Serial->changeSerialSettings(mPortSettings);
}

bool QSerialDevice::connectComPort()
{
	if (!portIsOpened()) {
		return m_Serial->openSerialPort(mPortSettings->mPortName, mPortSettings->mBaudRate, mPortSettings->mDataBits, mPortSettings->mParity, mPortSettings->mStopBits, mPortSettings->mFlowControl);
	}
	return true;
}

void QSerialDevice::closeComPort()
{
	m_Serial->closeSerialPort();
}

bool QSerialDevice::portIsOpened()
{
	return m_Serial->isOpen();
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

void QSerialDevice::handleCommandTimeout(SerialCommand command, QList<QVariant> params, int port)
{
	emit commandTimeout(port);
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Helper Methods
///////////////////////////////////////////////////////////////////////////////////////////////

bool QSerialDevice::fileExists(QString fileName)
{
	QFileInfo check_file(QDir::currentPath() + "/" + fileName + ".ini");
	return (check_file.exists() && check_file.isFile());
}