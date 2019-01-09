#include "QSerialResponseAnalyzer.h"
#include "SerialCommand.h"

QSerialResponseAnalyzer::QSerialResponseAnalyzer(QSerialBuffer & serialBuffer, const SerialMessages & serialMessages) :
	m_serialBuffer{ serialBuffer },
	m_serialMessages{ serialMessages }
{
}


QSerialResponseAnalyzer::QSerialResponseAnalyzer(QSerialBuffer & serialBuffer)
	: QSerialResponseAnalyzer(serialBuffer, SerialMessages())
{
}


QSerialResponseAnalyzer::~QSerialResponseAnalyzer()
{
}

/*! À chaque réponse reçue, le tampon m_responseBuffer est analysé pour trouver toutes les réponses qui correspondent à l'une des commandes dans m_sentCommandList.
*	Les tampons sont gérés en fonction du mode d'opération de chaque commande.
*
*/
void QSerialResponseAnalyzer::analyzeResponses()
{
	QList<SerialCommand>::iterator sentCmdIterator = m_serialBuffer.sentCommandsBegin();
	while (sentCmdIterator != m_serialBuffer.sentCommandsEnd() && m_serialBuffer.sentCommandListSize() != 0)
	{
		const SerialCommand & command = *sentCmdIterator;
		QByteArray response = takeMatchingResponse(command);
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
					response = takeMatchingResponse(command);
				}
			}
		}
		++sentCmdIterator;
	}

	// if the device is able to send messages on its own (not a getCommand response), and there is something left in the buffer.
	if (!m_serialMessages.isEmpty() && !m_serialBuffer.isResponseBufferEmpty())
	{
		QByteArrayList receivedMessageList = m_responseMatcher.getMessageMatchList(m_serialBuffer.getResponseBuffer());
		for (const QByteArray & receivedMessage : receivedMessageList)
		{
			m_serialBuffer.removeMatchedResponse(receivedMessage);
			emit foundMessage(receivedMessage, m_serialMessages.getTranslation(receivedMessage));
		}
	}
}

QByteArray QSerialResponseAnalyzer::takeMatchingResponse(const SerialCommand & command)
{
	QByteArray matchingResponse = m_responseMatcher.getFirstCommandMatch(m_serialBuffer.getResponseBuffer(), command);

	if (!matchingResponse.isNull())
	{
		m_serialBuffer.removeMatchedResponse(matchingResponse);
	}
	return matchingResponse;
}
