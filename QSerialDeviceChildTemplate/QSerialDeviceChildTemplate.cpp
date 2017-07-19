#include "Q_BME280.h"

#include <QDebug>


const QString Q_BME280::CMD_GET_TEMPERATURE { "GetTemperature" };
const QString Q_BME280::CMD_GET_PRESSURE { "GetPressure" };
const QString Q_BME280::CMD_GET_HUMIDITY { "GetHumidity" };


Q_BME280::Q_BME280(QCommandSerialPort * sharedSerial, SerialSettings * settings, QObject *parent)
	:
	QSerialDevice(sharedSerial, settings, parent)
{
	init();
}

Q_BME280::~Q_BME280()
{
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Slots
///////////////////////////////////////////////////////////////////////////////////////////////

void Q_BME280::handleMatchingResponse(const QByteArray &response, const SerialCommand &command)
{
	qDebug() << command.name() + " : " + response;
}

void Q_BME280::handleMessageReceived(QString const &message) {
	//emit messageReceived(mDeviceMessages[message]);
	qDebug() << "Message from device : " << mDeviceMessages[message];
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////////////////////


void Q_BME280::initDevice() 
{
	// commandes d'initialisation de l'appareil ici...

	sendBlockingCommand(Command::SoftReset);
}

void Q_BME280::fillDictionary()
{
	mSerialCommands[CMD_GET_TEMPERATURE] = new SerialCommand(				
		mUSBtoI2C.toRead(BME280_ADDRESS, BME280_REG_TEMPDATA, 3),           	// cmd
		"GetTemperature",                                                   	// name
		SerialCommand::IOType::Out,                                         	// IOType
		0,                                                                  	// nb of params
		false,                                                              	// params are byte arrays
		SerialOperationMode::BlockingMode::Blocking,                        	// BlockingMode
		SerialOperationMode::FluxMode::Pull,                                	// FluxMode	
		"",                                                                 	// eol car
		"",                                                                 	// separator
		"Operation",                                                        	// family
		"Get temperature data",                                             	// short desc
		3                                                                       // nb of expected bytes
	);

	mSerialCommands[CMD_GET_PRESSURE] = new SerialCommand(
		mUSBtoI2C.toRead(BME280_ADDRESS, BME280_REG_PRESSUREDATA, 3),
		"GetPressure",
		SerialCommand::IOType::Out,
		0,
		false,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		"",
		"Operation",
		"Get pressure data",
		3
	);

	mSerialCommands[CMD_GET_HUMIDITY] = new SerialCommand(
		mUSBtoI2C.toRead(BME280_ADDRESS, BME280_REG_HUMIDDATA, 2),
		"GetHumidity",
		SerialCommand::IOType::Out,
		0,
		false,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		"",
		"Operation",
		"Get humidity data",
		2
	);
}

void Q_BME280::fillDeviceMessages()
{

}