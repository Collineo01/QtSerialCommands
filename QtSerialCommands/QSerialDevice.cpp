/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/

#include "QSerialDevice.h"
#include "SerialPortSettings.h"

#include <QDebug>
#include <QDir>
#include "SerialCommand.h"


QString const QSerialDevice::DEFAULT_INI{ "defaultPortSettings" };
QString const QSerialDevice::CURRENT_INI{ "currentPortSettings" };
QString const QSerialDevice::TEMP_INI{ "tempSettings" };

int const QSerialDevice::DEFAULT_PORT{ -1 };


QSerialDevice::QSerialDevice(
	const SerialCommandFactory & commandFactory,
	const SerialMessageFactory & messageFactory,
	SerialPortSettings * settings,
	QMatchSerialPort * sharedSerial,
	QObject * parent
) :
	QObject(parent),
	m_serialCommands{ commandFactory.createSerialCommands() },
	m_deviceMessages{ messageFactory.createSerialMessages() },
	m_portSettings{ settings == nullptr ? new SerialPortSettings(DEFAULT_PORT) : settings },
	m_serialPort{ sharedSerial == nullptr ? new QMatchSerialPort(messageFactory) : sharedSerial }
{
	connect(m_serialPort, &QMatchSerialPort::matchingResponseReceived, this, &QSerialDevice::handleMatchingResponse);
	connect(m_serialPort, &QMatchSerialPort::messageReceived, this, &QSerialDevice::handleMessageReceived);
	connect(m_serialPort, &QMatchSerialPort::messageReceived, this, &QSerialDevice::messageReceived);
	connect(m_serialPort, &QAsyncSerialPort::connectionUpdated, this, &QSerialDevice::handleConnectionUpdated);
	connect(m_serialPort, &QAsyncSerialPort::connectionUpdated, this, &QSerialDevice::connectionUpdated);
	connect(m_serialPort, &QMatchSerialPort::commandTimedOut, this, &QSerialDevice::commandTimedOut);
	connect(m_serialPort, &QMatchSerialPort::commandTimedOut, this, &QSerialDevice::handleCommandTimedOut);

	// Initialiser les paramètres de connexion série
	//initPortSettings();
}

QSerialDevice::QSerialDevice(
	const SerialCommandFactory & commandFactory,
	SerialPortSettings * settings,
	QMatchSerialPort * sharedSerial,
	QObject * parent
) :
	QSerialDevice(commandFactory, DummySerialMessageFactory(), settings, sharedSerial, parent)
{
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
		qDebug() << "Connection successful on " + m_serialPort->portName();
	}
	else if (connectionFailed)
	{
		qDebug() << "Connection failed on " + m_serialPort->portName();
	}
	else
	{
		qDebug() << "Connection closed on " + m_serialPort->portName();
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////////////////////

void QSerialDevice::setTimeout(int timeout)
{
	m_serialPort->m_timeout = timeout;
}

void QSerialDevice::sendCommand(const QString & commandKey, QList<SerialCommandArg> args)
{
	// TODO : throw exception if not connected instead of connecting.
	bool connected = true;

	if (!isConnected())
	{
		changePort(m_portSettings->getPort());
		connected = connectPort();
	}

	if (connected)
	{
		m_serialPort->setBypassingSmartMatchingMode(false);
		SerialCommand command = *m_serialCommands[commandKey];
		command.setArgs(args);
		emit m_serialPort->sendCommandRequested(command);
	}
	else
	{
		qDebug() << "Connection failed on " + m_serialPort->portName();
	}
}

QByteArray QSerialDevice::sendBlockingCommand(const QString & commandKey, QList<SerialCommandArg> args)
{
	bool connected = true;

	if (!isConnected())
	{
		changePort(m_portSettings->getPort());
		connected = connectPort();
	}

	if (connected)
	{
		SerialCommand command = *m_serialCommands[commandKey];
		QByteArray response = m_serialPort->sendBlockingCommandSync(command, args);
		//qDebug() << "BlockingResponse : " << response;
		return response;
	}

	qDebug() << "Connection failed on " + m_serialPort->portName();
	return QByteArray();
}

void QSerialDevice::changePort(int port)
{
	if (port <= 0)
	{
		throw std::invalid_argument("Serial getPort number invalid : must be greater than 0.");
	}

	m_portSettings->setPort(port);
	m_serialPort->changeSerialPortSettings(m_portSettings);
}

bool QSerialDevice::connectPort()
{
	if (!isConnected())
	{
		return m_serialPort->openPort(m_portSettings);
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
	m_serialPort->closePort();
}

bool QSerialDevice::isConnected()
{
	return m_serialPort->isOpen();
}

/*! Affectation de m_settings à partir d'un fichier ini sauvegardé. Si aucun n'est sauvegardé, c'est ici qu'on en crée un avec des paramètres par défaut.
*/
void QSerialDevice::initPortSettings()
{
	// Fichier avec parametres modifies existant (ATTENTION : Si le fichier existe déjà, il utilisera le SerialPortSettings contenu avant celui passé dans le constructeur)
	if (fileExists(CURRENT_INI))
	{
		m_portSettings->load(CURRENT_INI);
	}
	// Si un QSerialSetings est passé au constructeur
	else if (m_portSettings != nullptr)
	{
		m_portSettings->save(CURRENT_INI);
	}
	else
	{
		// Default Settings
		m_portSettings = new SerialPortSettings(DEFAULT_PORT);

		// Sauvegarde du default si non existant
		if (!fileExists(DEFAULT_INI))
		{
			m_portSettings->save(DEFAULT_INI);
		}
	}
}

void QSerialDevice::handleCommandTimedOut(QString commandKey, QList<SerialCommandArg> args, int port)
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