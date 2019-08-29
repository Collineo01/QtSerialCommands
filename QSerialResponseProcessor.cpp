#include "QSerialResponseProcessor.h"


QSerialResponseProcessor::QSerialResponseProcessor(QSerialBuffer & serialBuffer, const SerialMessages & serialMessages) :
	m_serialBuffer{ serialBuffer },
	m_serialMessages{ serialMessages }
{
}


QSerialResponseProcessor::QSerialResponseProcessor(QSerialBuffer & serialBuffer)
	: QSerialResponseProcessor(serialBuffer, SerialMessages())
{
}


QSerialResponseProcessor::~QSerialResponseProcessor()
{
}

void QSerialResponseProcessor::processResponses()
{
	QList<SerialCommand>::iterator sentCmdIterator = m_serialBuffer.getSentCommandsBegin();
	while (
		sentCmdIterator != m_serialBuffer.getSentCommandsEnd() 
		&& m_serialBuffer.getSentCommandListSize() > 0
		&& !m_serialBuffer.isResponseBufferEmpty())
	{
		SerialCommand command = *sentCmdIterator;
		QByteArray response = takeCommandFirstMatch(command);
		if (!response.isNull())
		{
			emit foundMatchingResponse(response, command);

			// Pull mode
			if (command.getOperationMode().fluxMode() == SerialOperationMode::FluxMode::Pull)
			{
				sentCmdIterator = m_serialBuffer.eraseSentCommand(sentCmdIterator);
				if (command.getOperationMode().blockingMode() == SerialOperationMode::BlockingMode::Blocking
					&& m_serialBuffer.hasNextCommandToSend())
				{
					emit nextCommandReadyToSend(); // we waited for the response, now we can send the next command.
				}
				continue;
			}
			// Push mode
			else {
				while (!response.isNull())
				{
					emit foundMatchingResponse(response, command);
					response = takeCommandFirstMatch(command);
				}
			}
		}
		++sentCmdIterator;
	}

	takeMessages();
}

QByteArray QSerialResponseProcessor::takeCommandFirstMatch(const SerialCommand & command) const
{
	QByteArray matchingResponse = m_responseMatcher.getCommandFirstMatch(m_serialBuffer.getResponseBuffer(), command);

	if (!matchingResponse.isNull())
	{
		m_serialBuffer.removeMatchedResponse(matchingResponse);
	}
	return matchingResponse;
}

void QSerialResponseProcessor::takeMessages()
{
	QByteArrayList receivedMessageList = m_responseMatcher.getMessages(m_serialBuffer.getResponseBuffer());
	for (const QByteArray & receivedMessage : receivedMessageList)
	{
		m_serialBuffer.removeMatchedResponses(receivedMessageList);
		emit foundMessage(receivedMessage, m_serialMessages.getDescription(receivedMessage));
	}
}
