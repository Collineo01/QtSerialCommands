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

/*! À chaque réponse reçue, le tampon m_responseBuffer est analysé pour trouver toutes les réponses qui correspondent à l'une des commandes dans m_sentCommandList.
*	Les tampons sont gérés en fonction du mode d'opération de chaque commande.
*
*/
void QSerialResponseProcessor::processResponses()
{
	QList<SerialCommand>::iterator sentCmdIterator = m_serialBuffer.getSentCommandsBegin();
	while (sentCmdIterator != m_serialBuffer.getSentCommandsEnd() && m_serialBuffer.sentCommandListSize() != 0)
	{
		const SerialCommand & command = *sentCmdIterator;
		QByteArray response = takeCommandFirstMatch(command);
		if (!response.isNull())
		{
			emit foundMatchingResponse(response, command);

			// Pull mode
			if (command.getOperationMode().fluxMode() == SerialOperationMode::FluxMode::Pull)
			{
				if (command.getOperationMode().blockingMode() == SerialOperationMode::BlockingMode::Blocking)
				{
					sentCmdIterator = m_serialBuffer.eraseSentCommand(sentCmdIterator);
					emit commandIsReadyToSend(m_serialBuffer.getNextCommandToSend()); // we waited for the response, now we can send the next getCommand
				}
				else {
					sentCmdIterator = m_serialBuffer.eraseSentCommand(sentCmdIterator);
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
		m_serialBuffer.removeMatchedCommand(command);
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
