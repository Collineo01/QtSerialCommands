#pragma once



#include "QAsyncSerialPort.h"

/*! \class SerialPortSettings
*
*	\brief Conteneur des paramètres d'un appareil de communication série. Permet la sauvegarde et le chargement de fichier ini.
*
*	save() pour sauvegarder et load() pour charger.
*
*/


class SerialPortSettings
{

public:
	SerialPortSettings(
		int port,
		QAsyncSerialPort::BaudRate baudRate = DEFAULT_BAUD_RATE,
		QAsyncSerialPort::StopBits stopBits = DEFAULT_STOP_BITS,
		QAsyncSerialPort::DataBits dataBits = DEFAULT_DATA_BITS,
		QAsyncSerialPort::Parity parity = DEFAULT_PARITY,
		QAsyncSerialPort::FlowControl flowControl = DEFAULT_FLOW_CONTROL
	);
	~SerialPortSettings();

	static const QString KEY_PORT;
	static const QString KEY_BAUDRATE;
	static const QString KEY_STOPBITS;
	static const QString KEY_DATABITS;
	static const QString KEY_PARITY;
	static const QString KEY_FLOWCONTROL;

	static const QAsyncSerialPort::BaudRate		DEFAULT_BAUD_RATE;
	static const QAsyncSerialPort::StopBits		DEFAULT_STOP_BITS;
	static const QAsyncSerialPort::DataBits		DEFAULT_DATA_BITS;
	static const QAsyncSerialPort::Parity		DEFAULT_PARITY;
	static const QAsyncSerialPort::FlowControl	DEFAULT_FLOW_CONTROL;

	void save(QString fileName);
	void load(QString fileName);
	bool isValid();

	int getPort() const { return m_Port; };
	QAsyncSerialPort::BaudRate getBaudRate() const { return m_BaudRate; }
	QAsyncSerialPort::StopBits  getStopBits() const { return m_StopBits; }
	QAsyncSerialPort::DataBits getDataBits() const { return m_DataBits; }
	QAsyncSerialPort::Parity getParity() const { return m_Parity; }
	QAsyncSerialPort::FlowControl getFlowControl() const { return m_FlowControl; }

	void setPort(int port) { m_Port = port; }

private:
	int m_Port;
	QAsyncSerialPort::BaudRate m_BaudRate;
	QAsyncSerialPort::StopBits m_StopBits;
	QAsyncSerialPort::DataBits m_DataBits;
	QAsyncSerialPort::Parity m_Parity;
	QAsyncSerialPort::FlowControl m_FlowControl;
};
