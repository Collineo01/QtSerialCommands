#pragma once

#include "qtserialcommands_global.h"

#include <QObject>
#include "QSerialBuffer.h"

class SerialCommand;

class QTSERIALCOMMANDS_EXPORT QSerialCommandManager : public QObject
{
	Q_OBJECT

public:
	QSerialCommandManager(QSerialBuffer & serialBuffer);
	~QSerialCommandManager();

public slots:
	void manageCommandToSend();

signals:
	void commandIsReadyToSend(SerialCommand command);

private:
	QSerialBuffer & m_serialBuffer;
};
