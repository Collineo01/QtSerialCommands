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

int const QSerialDevice::DEFAULT_COM_PORT{ -1 };


QSerialDevice::QSerialDevice(QCommandSerialPort * sharedSerial, SerialSettings * settings, QObject *parent)
	:
	QObject(parent),
	m_PortSettings{ settings }, // TODO : remplacer par une instance au lieu d'un pointeur (doit créer le copy constructor)
	m_Serial{ sharedSerial },
	m_Port{ -1 }
{
	if (sharedSerial == nullptr)
	{
		m_Serial = new QCommandSerialPort;
	}
	if (settings == nullptr)
	{
		m_PortSettings = new SerialSettings(DEFAULT_COM_PORT);
	}

	connect(m_Serial, &QCommandSerialPort::responseMatchingCommandReceived, this, &QSerialDevice::handleMatchingResponse);
	connect(m_Serial, &QCommandSerialPort::responseMatchingCommandReceived, this, &QSerialDevice::responseMatchingCommandReceived);
	connect(m_Serial, &QCommandSerialPort::messageReceived, this, &QSerialDevice::handleMessageReceived);
	connect(m_Serial, &QCommandSerialPort::messageReceived, this, &QSerialDevice::messageReceived);
	connect(m_Serial, &QAsyncSerialPort::connectionUpdated, this, &QSerialDevice::handleConnectionUpdated);
	connect(m_Serial, &QAsyncSerialPort::connectionUpdated, this, &QSerialDevice::connectionUpdated);
	connect(m_Serial, &QCommandSerialPort::commandTimedOut, this, &QSerialDevice::commandTimedOut);
	connect(m_Serial, &QCommandSerialPort::commandTimedOut, this, &QSerialDevice::handleCommandTimedOut);

	// Initialiser les paramètres de connexion série
	//initPortSettings();
}

QSerialDevice::QSerialDevice(QMap<QString, SerialCommand const *> serialCommands, QMap<QString, QString> deviceMessages, 
							QCommandSerialPort * sharedSerial, SerialSettings * settings, QObject *parent)
	:
	QSerialDevice(sharedSerial, settings, parent)

{
	m_SerialCommands = serialCommands;
	m_DeviceMessages = deviceMessages;

	if (sharedSerial == nullptr)
	{
		m_Serial = new QCommandSerialPort;
	}
	if (settings == nullptr)
	{
		m_PortSettings = new SerialSettings(DEFAULT_COM_PORT);
	}

	connect(m_Serial, &QCommandSerialPort::responseMatchingCommandReceived, this, &QSerialDevice::handleMatchingResponse);
	connect(m_Serial, &QCommandSerialPort::responseMatchingCommandReceived, this, &QSerialDevice::responseMatchingCommandReceived);
	connect(m_Serial, &QCommandSerialPort::messageReceived, this, &QSerialDevice::handleMessageReceived);
	connect(m_Serial, &QCommandSerialPort::messageReceived, this, &QSerialDevice::messageReceived);
	connect(m_Serial, &QAsyncSerialPort::connectionUpdated, this, &QSerialDevice::handleConnectionUpdated);
	connect(m_Serial, &QAsyncSerialPort::connectionUpdated, this, &QSerialDevice::connectionUpdated);
	connect(m_Serial, &QCommandSerialPort::commandTimedOut, this, &QSerialDevice::handleCommandTimedOut);

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

void QSerialDevice::setTimeout(int timeout)
{
	m_Serial->m_Timeout = timeout;
}

void QSerialDevice::sendCommand(SerialCommand command, QList<QVariant> args)
{
	bool connected = true;

	if (!isConnected()) 
	{
		changePort(m_Port);
		connected = connectPort();
	}

	if (connected)
	{
		m_Serial->setDevelopmentMode(false);
		/*QPair<SerialCommand const &, QList<QVariant>> commandAndParams(command, args);
		m_Serial->writeToBuffer(commandAndParams);*/
		command.setArguments(args);
		emit m_Serial->sendCommandRequest(command);
	}
	else
	{
		qDebug() << "Connection failed on " + m_Serial->portName();
	}
}

void QSerialDevice::sendCommand(QString commandKey, QList<QVariant> params)
{
	SerialCommand command = *m_SerialCommands[commandKey];
	sendCommand(command, params);
}

QByteArray QSerialDevice::sendBlockingCommand(QString commandKey, QList<QVariant> params)
{
	bool connected = true;

	if (!isConnected())
	{
		changePort(m_Port);
		connected = connectPort();
	}

	if (connected)
	{
		SerialCommand cmd = *m_SerialCommands[commandKey];
		QByteArray response = m_Serial->sendBlockingCommand(cmd, params);
		//qDebug() << "BlockingResponse : " << response;
		return response;
	}

	qDebug() << "Connection failed on " + m_Serial->portName();
	return QByteArray();
}

void QSerialDevice::init(QString terminator)
{
	// Remplir le dictionnaire de commandes
	fillDictionary();

	// Remplir le dictionnaire de messages
	fillDeviceMessages();

	// Messages que peut envoyer l'appareil (clés du dictionnaire de messages)
	m_Serial->setDeviceMessages(m_DeviceMessages.keys(), terminator);
}

void QSerialDevice::changePort(int port)
{
	if (port <= 0) 
	{
		throw std::invalid_argument("Serial port number invalid : must be greater than 0.");
	}

	m_PortSettings->m_Port = port;
	m_Serial->changeSerialSettings(m_PortSettings);
}

void QSerialDevice::clearCommandAndResponseBuffers()
{
	m_Serial->clearBuffers();
}

bool QSerialDevice::connectPort()
{
	if (!isConnected()) 
	{
		return m_Serial->openPort
		(
			m_PortSettings->m_Port, 
			m_PortSettings->m_BaudRate, 
			m_PortSettings->m_DataBits, 
			m_PortSettings->m_Parity, 
			m_PortSettings->m_StopBits, 
			m_PortSettings->m_FlowControl
		);
	}
	return true;
}

bool QSerialDevice::connectPort(int port)
{
	changePort(port);
	bool connected = connectPort();

	return connected;
}

void QSerialDevice::closePort()
{
	m_Serial->closePort();
}

bool QSerialDevice::isConnected()
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
		m_PortSettings->load(CURRENT_INI);
	}
	// Si un QSerialSetings est passé au constructeur
	else if (m_PortSettings != nullptr)
	{
		m_PortSettings->save(CURRENT_INI);
	}
	else
	{
		// Default Settings
		m_PortSettings = new SerialSettings(DEFAULT_COM_PORT);

		// Sauvegarde du default si non existant
		if (!fileExists(DEFAULT_INI))
		{
			m_PortSettings->save(DEFAULT_INI);
		}
	}
}

void QSerialDevice::handleCommandTimedOut(QString command, QList<QVariant> args, int port)
{
	emit portTimedOut(port);
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Helper Methods
///////////////////////////////////////////////////////////////////////////////////////////////

bool QSerialDevice::fileExists(QString fileName)
{
	QFileInfo check_file(QDir::currentPath() + "/" + fileName + ".ini");
	return (check_file.exists() && check_file.isFile());
}