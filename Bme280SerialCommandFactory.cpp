#include "Bme280SerialCommandFactory.h"

const QString Bme280SerialCommandFactory::CMD_GET_PTH{ "GetPTH" };
const QString Bme280SerialCommandFactory::CMD_SOFT_RESET{ "SoftReset" };
const QString Bme280SerialCommandFactory::CMD_GET_STATUS{ "GetStatus" };

const QString Bme280SerialCommandFactory::CMD_GET_DIG_T1{ "GetDigT1" };
const QString Bme280SerialCommandFactory::CMD_GET_DIG_T2{ "GetDigT2" };
const QString Bme280SerialCommandFactory::CMD_GET_DIG_T3{ "GetDigT3" };

const QString Bme280SerialCommandFactory::CMD_GET_DIG_P1{ "GetDigP1" };
const QString Bme280SerialCommandFactory::CMD_GET_DIG_P2{ "GetDigP2" };
const QString Bme280SerialCommandFactory::CMD_GET_DIG_P3{ "GetDigP3" };
const QString Bme280SerialCommandFactory::CMD_GET_DIG_P4{ "GetDigP4" };
const QString Bme280SerialCommandFactory::CMD_GET_DIG_P5{ "GetDigP5" };
const QString Bme280SerialCommandFactory::CMD_GET_DIG_P6{ "GetDigP6" };
const QString Bme280SerialCommandFactory::CMD_GET_DIG_P7{ "GetDigP7" };
const QString Bme280SerialCommandFactory::CMD_GET_DIG_P8{ "GetDigP8" };
const QString Bme280SerialCommandFactory::CMD_GET_DIG_P9{ "GetDigP9" };

const QString Bme280SerialCommandFactory::CMD_GET_DIG_H1{ "GetDigH1" };
const QString Bme280SerialCommandFactory::CMD_GET_DIG_H2{ "GetDigH2" };
const QString Bme280SerialCommandFactory::CMD_GET_DIG_H3{ "GetDigH3" };
const QString Bme280SerialCommandFactory::CMD_GET_DIG_H4{ "GetDigH4" };
const QString Bme280SerialCommandFactory::CMD_GET_DIG_H5{ "GetDigH5" };
const QString Bme280SerialCommandFactory::CMD_GET_DIG_H6{ "GetDigH6" };

const QString Bme280SerialCommandFactory::CMD_CONNECTED{ "Bme280Connected" };

const QString Bme280SerialCommandFactory::CMD_CONTROL_HUMID{ "ControlHumid" };
const QString Bme280SerialCommandFactory::CMD_CONFIG{ "Config" };
const QString Bme280SerialCommandFactory::CMD_CONTROL{ "Control" };

const QString Bme280SerialCommandFactory::CMD_GET_TEMPERATURE{ "GetTemperature" };
const QString Bme280SerialCommandFactory::CMD_GET_PRESSURE{ "GetPressure" };
const QString Bme280SerialCommandFactory::CMD_GET_HUMIDITY{ "GetHumidity" };

Bme280SerialCommandFactory::Bme280SerialCommandFactory()
{
}


Bme280SerialCommandFactory::~Bme280SerialCommandFactory()
{
}

QMap<QString, const SerialCommand*> Bme280SerialCommandFactory::createSerialCommands() const
{
	QMap<QString, const SerialCommand*> commands;

	commands[CMD_GET_PTH] = new SerialCommand(
		m_usbToI2C.toRead(BME280_ADDRESS, BME280_REG_PRESSUREDATA, 8),		// cmd
		CMD_GET_PTH,														// name
		8,																	// nb of expected bytes
		SerialOperationMode::BlockingMode::Blocking,						// BlockingMode
		SerialOperationMode::FluxMode::Pull,								// FluxMode
		"",																	// eol car
		0,																	// # params
		"",																	// separator
		IOType::Out,														// IOType
		"Operation",														// family
		"Get current pressure, temperature, and humidity"					// short desc														
	);

	commands[CMD_CONNECTED] = new SerialCommand(
		m_usbToI2C.toDeviceConnected(BME280_ADDRESS),
		CMD_CONNECTED,
		1,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::Out,
		"Operation",
		"Check if the BME280 is connected"
	);

	commands[CMD_SOFT_RESET] = new SerialCommand(
		m_usbToI2C.toWrite(BME280_ADDRESS, BME280_REG_SOFTRESET, 1, QByteArrayLiteral("\xB6")),
		CMD_SOFT_RESET,
		QByteArrayList({ QByteArrayLiteral("\x1") }),
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::In,
		"Operation",
		"Reset the device using soft-reset"
	);

	commands[CMD_GET_STATUS] = new SerialCommand(
		m_usbToI2C.toRead(BME280_ADDRESS, BME280_REG_STATUS, 1),
		CMD_GET_STATUS,
		1,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::Out,
		"Operation",
		"Get status : if value is 1, it is reading calibration data"
	);

	commands[CMD_GET_DIG_T1] = new SerialCommand(
		m_usbToI2C.toRead(BME280_ADDRESS, BME280_REG_DIG_T1, 2),
		CMD_GET_DIG_T1,
		2,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::Out,
		"Operation",
		"Get calibration data 1 for temperature"
	);

	commands[CMD_GET_DIG_T2] = new SerialCommand(
		m_usbToI2C.toRead(BME280_ADDRESS, BME280_REG_DIG_T2, 2),
		CMD_GET_DIG_T2,
		2,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::Out,
		"Operation",
		"Get calibration data 2 for temperature"
	);

	commands[CMD_GET_DIG_T3] = new SerialCommand(
		m_usbToI2C.toRead(BME280_ADDRESS, BME280_REG_DIG_T3, 2),
		CMD_GET_DIG_T3,
		2,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::Out,
		"Operation",
		"Get calibration data 3 for temperature"
	);

	commands[CMD_GET_DIG_P1] = new SerialCommand(
		m_usbToI2C.toRead(BME280_ADDRESS, BME280_REG_DIG_P1, 2),
		CMD_GET_DIG_P1,
		2,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::Out,
		"Operation",
		"Get calibration data 1 for pressure"
	);

	commands[CMD_GET_DIG_P2] = new SerialCommand(
		m_usbToI2C.toRead(BME280_ADDRESS, BME280_REG_DIG_P2, 2),
		CMD_GET_DIG_P2,
		2,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::Out,
		"Operation",
		"Get calibration data 2 for pressure"
	);

	commands[CMD_GET_DIG_P3] = new SerialCommand(
		m_usbToI2C.toRead(BME280_ADDRESS, BME280_REG_DIG_P3, 2),
		CMD_GET_DIG_P3,
		2,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::Out,
		"Operation",
		"Get calibration data 3 for pressure"
	);

	commands[CMD_GET_DIG_P4] = new SerialCommand(
		m_usbToI2C.toRead(BME280_ADDRESS, BME280_REG_DIG_P4, 2),
		CMD_GET_DIG_P4,
		2,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::Out,
		"Operation",
		"Get calibration data 4 for pressure"
	);

	commands[CMD_GET_DIG_P5] = new SerialCommand(
		m_usbToI2C.toRead(BME280_ADDRESS, BME280_REG_DIG_P5, 2),
		CMD_GET_DIG_P5,
		2,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::Out,
		"Operation",
		"Get calibration data 5 for pressure"
	);

	commands[CMD_GET_DIG_P6] = new SerialCommand(
		m_usbToI2C.toRead(BME280_ADDRESS, BME280_REG_DIG_P6, 2),
		CMD_GET_DIG_P6,
		2,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::Out,
		"Operation",
		"Get calibration data 6 for pressure"
	);

	commands[CMD_GET_DIG_P7] = new SerialCommand(
		m_usbToI2C.toRead(BME280_ADDRESS, BME280_REG_DIG_P7, 2),
		CMD_GET_DIG_P7,
		2,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::Out,
		"Operation",
		"Get calibration data 7 for pressure"
	);

	commands[CMD_GET_DIG_P8] = new SerialCommand(
		m_usbToI2C.toRead(BME280_ADDRESS, BME280_REG_DIG_P8, 2),
		CMD_GET_DIG_P8,
		2,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::Out,
		"Operation",
		"Get calibration data 8 for pressure"
	);

	commands[CMD_GET_DIG_P9] = new SerialCommand(
		m_usbToI2C.toRead(BME280_ADDRESS, BME280_REG_DIG_P9, 2),
		CMD_GET_DIG_P9,
		2,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::Out,
		"Operation",
		"Get calibration data 9 for pressure"
	);

	commands[CMD_GET_DIG_H1] = new SerialCommand(
		m_usbToI2C.toRead(BME280_ADDRESS, BME280_REG_DIG_H1, 1),
		CMD_GET_DIG_H1,
		1,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::Out,
		"Operation",
		"Get calibration data 1 for humidity"
	);

	commands[CMD_GET_DIG_H2] = new SerialCommand(
		m_usbToI2C.toRead(BME280_ADDRESS, BME280_REG_DIG_H2, 2),
		CMD_GET_DIG_H2,
		2,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::Out,
		"Operation",
		"Get calibration data 2 for humidity"
	);

	commands[CMD_GET_DIG_H3] = new SerialCommand(
		m_usbToI2C.toRead(BME280_ADDRESS, BME280_REG_DIG_H3, 1),
		CMD_GET_DIG_H3,
		1,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::Out,
		"Operation",
		"Get calibration data 3 for humidity"
	);

	commands[CMD_GET_DIG_H4] = new SerialCommand(
		m_usbToI2C.toRead(BME280_ADDRESS, BME280_REG_DIG_H4, 1),
		CMD_GET_DIG_H4,
		1,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::Out,
		"Operation",
		"Get calibration data 4 for humidity"
	);

	commands[CMD_GET_DIG_H5] = new SerialCommand(
		m_usbToI2C.toRead(BME280_ADDRESS, BME280_REG_DIG_H5, 1),
		CMD_GET_DIG_H5,
		1,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::Out,
		"Operation",
		"Get calibration data 5 for humidity"
	);

	commands[CMD_GET_DIG_H6] = new SerialCommand(
		m_usbToI2C.toRead(BME280_ADDRESS, BME280_REG_DIG_H6, 1),
		CMD_GET_DIG_H6,
		1,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::Out,
		"Operation",
		"Get calibration data 6 for humidity"
	);

	commands[CMD_CONTROL_HUMID] = new SerialCommand(
		m_usbToI2C.toWrite(BME280_ADDRESS, BME280_REG_CONTROLHUMID, 1),
		CMD_CONTROL_HUMID,
		QList<QByteArray>({ QByteArrayLiteral("\x01") }),
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		1,
		"",
		IOType::In,
		"Operation",
		"Control humidity"
	);

	commands[CMD_CONFIG] = new SerialCommand(
		m_usbToI2C.toWrite(BME280_ADDRESS, BME280_REG_CONFIG, 1),
		CMD_CONFIG,
		QList<QByteArray>({ QByteArrayLiteral("\x01") }),
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		1,
		"",
		IOType::In,
		"Operation",
		"Configuration"
	);

	commands[CMD_CONTROL] = new SerialCommand(
		m_usbToI2C.toWrite(BME280_ADDRESS, BME280_REG_CONTROL, 1),
		CMD_CONTROL,
		QList<QByteArray>({ QByteArrayLiteral("\x01") }),
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		1,
		"",
		IOType::In,
		"Operation",
		"Control"
	);

	commands[CMD_GET_TEMPERATURE] = new SerialCommand(
		m_usbToI2C.toRead(BME280_ADDRESS, BME280_REG_TEMPDATA, 3),
		CMD_GET_TEMPERATURE,
		3,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::Out,
		"Operation",
		"Get temperature data"
	);

	commands[CMD_GET_PRESSURE] = new SerialCommand(
		m_usbToI2C.toRead(BME280_ADDRESS, BME280_REG_PRESSUREDATA, 3),
		CMD_GET_PRESSURE,
		3,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::Out,
		"Operation",
		"Get pressure data"
	);

	commands[CMD_GET_HUMIDITY] = new SerialCommand(
		m_usbToI2C.toRead(BME280_ADDRESS, BME280_REG_HUMIDDATA, 2),
		CMD_GET_HUMIDITY,
		2,
		SerialOperationMode::BlockingMode::Blocking,
		SerialOperationMode::FluxMode::Pull,
		"",
		0,
		"",
		IOType::Out,
		"Operation",
		"Get humidity data"
	);

	return commands;
}
