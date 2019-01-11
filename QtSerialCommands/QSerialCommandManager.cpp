#include "QSerialCommandManager.h"
#include "SerialOperationMode.h"
#include "SerialCommand.h"
#include "QSerialBuffer.h"

QSerialCommandManager::QSerialCommandManager(QSerialBuffer & serialBuffer) :
	m_serialBuffer{ serialBuffer }
{
}

QSerialCommandManager::~QSerialCommandManager()
{
}

void QSerialCommandManager::manageCommandToSend()
{
	SerialCommand commandToSend = m_serialBuffer.getNextCommandToSend();
	const SerialOperationMode::BlockingMode & blockingMode = commandToSend.getOperationMode().blockingMode();

	QList<SerialCommand>::iterator sentCmdIterator = m_serialBuffer.sentCommandsBegin();
	while (sentCmdIterator != m_serialBuffer.sentCommandsEnd())
	{
		SerialCommand &command = *sentCmdIterator;
		// Push mode
		if (command.getOperationMode().fluxMode() == SerialOperationMode::FluxMode::Push)
		{
			if (command.stopsPushMode(commandToSend))
			{
				sentCmdIterator = m_serialBuffer.eraseSentCommand(sentCmdIterator);
			}
		}
		++sentCmdIterator;
	}
	if (blockingMode == SerialOperationMode::BlockingMode::NonBlockingNoResponse)
	{
		m_serialBuffer.removeNextCommandToSend();
		emit commandIsReadyToSend(commandToSend);
	}
	else if (
		blockingMode == SerialOperationMode::BlockingMode::NonBlockingXCommandsXResponses
		|| blockingMode == SerialOperationMode::BlockingMode::NonBlockingXCommandsOneResponse)
	{
		m_serialBuffer.moveNextCmdToSentBuffer();
		emit commandIsReadyToSend(commandToSend);
	}
	else if (blockingMode == SerialOperationMode::BlockingMode::Blocking)
	{
		m_serialBuffer.moveNextCmdToSentBuffer();
	}
}
