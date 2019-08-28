#pragma once

#include "SerialCommandFactory.h"
#include "UsbToI2C.h"

/*=========================================================================
I2C ADDRESS/BITS
-----------------------------------------------------------------------*/
#define BME280_ADDRESS                (0x76)
/*=========================================================================*/

class Bme280SerialCommandFactory :
	public SerialCommandFactory
{
public:

	/*=========================================================================
	REGISTERS
	-----------------------------------------------------------------------*/
	enum
	{
		BME280_REG_DIG_T1 = 0x88,
		BME280_REG_DIG_T2 = 0x8A,
		BME280_REG_DIG_T3 = 0x8C,

		BME280_REG_DIG_P1 = 0x8E,
		BME280_REG_DIG_P2 = 0x90,
		BME280_REG_DIG_P3 = 0x92,
		BME280_REG_DIG_P4 = 0x94,
		BME280_REG_DIG_P5 = 0x96,
		BME280_REG_DIG_P6 = 0x98,
		BME280_REG_DIG_P7 = 0x9A,
		BME280_REG_DIG_P8 = 0x9C,
		BME280_REG_DIG_P9 = 0x9E,

		BME280_REG_DIG_H1 = 0xA1,
		BME280_REG_DIG_H2 = 0xE1,
		BME280_REG_DIG_H3 = 0xE3,
		BME280_REG_DIG_H4 = 0xE4,
		BME280_REG_DIG_H5 = 0xE5,
		BME280_REG_DIG_H6 = 0xE7,

		BME280_REG_CHIPID = 0xD0,
		BME280_REG_VERSION = 0xD1,
		BME280_REG_SOFTRESET = 0xE0,

		BME280_REG_CAL26 = 0xE1,  // R calibration stored in 0xE1-0xF0

		BME280_REG_CONTROLHUMID = 0xF2,
		BME280_REG_STATUS = 0XF3,
		BME280_REG_CONTROL = 0xF4,
		BME280_REG_CONFIG = 0xF5,
		BME280_REG_PRESSUREDATA = 0xF7,
		BME280_REG_TEMPDATA = 0xFA,
		BME280_REG_HUMIDDATA = 0xFD
	};

	static const QString CMD_GET_PTH;
	static const QString CMD_SOFT_RESET;
	static const QString CMD_GET_STATUS;

	static const QString CMD_GET_DIG_T1;
	static const QString CMD_GET_DIG_T2;
	static const QString CMD_GET_DIG_T3;

	static const QString CMD_GET_DIG_P1;
	static const QString CMD_GET_DIG_P2;
	static const QString CMD_GET_DIG_P3;
	static const QString CMD_GET_DIG_P4;
	static const QString CMD_GET_DIG_P5;
	static const QString CMD_GET_DIG_P6;
	static const QString CMD_GET_DIG_P7;
	static const QString CMD_GET_DIG_P8;
	static const QString CMD_GET_DIG_P9;

	static const QString CMD_GET_DIG_H1;
	static const QString CMD_GET_DIG_H2;
	static const QString CMD_GET_DIG_H3;
	static const QString CMD_GET_DIG_H4;
	static const QString CMD_GET_DIG_H5;
	static const QString CMD_GET_DIG_H6;

	static const QString CMD_CONNECTED;

	static const QString CMD_CONTROL_HUMID;
	static const QString CMD_CONFIG;
	static const QString CMD_CONTROL;

	static const QString CMD_GET_TEMPERATURE;
	static const QString CMD_GET_PRESSURE;
	static const QString CMD_GET_HUMIDITY;

	Bme280SerialCommandFactory();
	~Bme280SerialCommandFactory();

	// Inherited via SerialCommandFactory
	QMap<QString, const SerialCommand*> createSerialCommands() const override;

private:
	UsbToI2C m_usbToI2C;
};

