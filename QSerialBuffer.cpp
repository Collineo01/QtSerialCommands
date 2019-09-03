#include "QSerialBuffer.h"

QSerialBuffer::QSerialBuffer(int sendBufferSize, int responsesBufferSize, QObject * parent) :
	QObject(parent),
	m_nbOfReadyCommands{ 0 },
	m_maxSendBufferSize{ sendBufferSize },
	m_maxResponseBufferSize{ responsesBufferSize },
	m_commandsToSendMutex{ QMutex::Recursive },
	m_sentCommandsMutex{ QMutex::Recursive },
	m_responsesMutex{ QMutex::Recursive }
{
}

QSerialBuffer::~QSerialBuffer()
{
}

bool QSerialBuffer::removeMatchedCommand(const SerialCommand & command)
{
	m_sentCommandsMutex.lock();
	bool success = m_sentCommandList.removeOne(command);
	m_sentCommandsMutex.unlock();

	return success;
}

void QSerialBuffer::removeMatchedResponse(const QByteArray & matchedResponse)
{
	m_responsesMutex.lock();
	m_responseBuffer.remove(m_responseBuffer.indexOf(matchedResponse), matchedResponse.length());
	m_responsesMutex.unlock();
}

void QSerialBuffer::removeMatchedResponses(const QByteArrayList & matchedResponses)
{
	m_responsesMutex.lock();
	for (QByteArray matchedResponse : matchedResponses)
	{
		QByteArray removedResponse = m_responseBuffer.remove(m_responseBuffer.indexOf(matchedResponse), matchedResponse.length());
	}
	m_responsesMutex.unlock();
}

void QSerialBuffer::removeNextCommandToSend()
{
	m_commandsToSendMutex.lock();
	m_commandToSendList.removeFirst();
	m_commandsToSendMutex.unlock();
}

QList<SerialCommand>::iterator QSerialBuffer::getSentCommandsBegin()
{
	return m_sentCommandList.begin();
}

QList<SerialCommand>::iterator QSerialBuffer::getSentCommandsEnd()
{
	return m_sentCommandList.end();
}

QList<SerialCommand>::iterator QSerialBuffer::eraseSentCommand(QList<SerialCommand>::iterator it)
{
	m_sentCommandsMutex.lock();
	QList<SerialCommand>::iterator iterator = m_sentCommandList.erase(it);
	m_sentCommandsMutex.unlock();

	return iterator;
}

int QSerialBuffer::getSentCommandListSize()
{
	m_sentCommandsMutex.lock();
	int size = m_sentCommandList.size();
	m_sentCommandsMutex.unlock();

	return size;
}

void QSerialBuffer::clearBuffers()
{
	m_commandsToSendMutex.lock();
	m_sentCommandsMutex.lock();
	m_responsesMutex.lock();

	m_commandToSendList.clear();
	m_sentCommandList.clear();
	m_responseBuffer.clear();

	m_commandsToSendMutex.unlock();
	m_sentCommandsMutex.unlock();
	m_responsesMutex.unlock();
}

SerialCommand QSerialBuffer::takeLastCommandSent()
{
	m_sentCommandsMutex.lock();
	SerialCommand command = m_sentCommandList.takeLast();
	m_sentCommandsMutex.unlock();

	return command;
}

QByteArray QSerialBuffer::getResponseBuffer()
{
	m_responsesMutex.lock();
	QByteArray responses = m_responseBuffer;
	m_responsesMutex.unlock();

	return responses;
}

bool QSerialBuffer::hasNextCommandToSend()
{
	m_responsesMutex.lock();
	bool hasNext = !m_commandToSendList.isEmpty();
	m_responsesMutex.unlock();

	return hasNext;
}

SerialCommand QSerialBuffer::getNextCommandToSend()
{
	m_commandsToSendMutex.lock();
	const SerialCommand  command = m_commandToSendList.constFirst();
	m_commandsToSendMutex.unlock();

	return command;
}

bool QSerialBuffer::isResponseBufferEmpty()
{
	m_responsesMutex.lock();
	bool bufferEmpty =  m_responseBuffer.isEmpty();
	m_responsesMutex.unlock();

	return bufferEmpty;
}

void QSerialBuffer::writeCommand(SerialCommand command)
{
	bool nextCommandReady = false;
	bool bufferFilled = false;

	m_commandsToSendMutex.lock();
	m_sentCommandsMutex.lock();

	const bool commandIsInBuffer = m_commandToSendList.contains(command) || m_sentCommandList.contains(command);
	const bool waitResponseBeforeSendingAgain = 
		commandIsInBuffer && command.getOperationMode().blockingMode() == SerialOperationMode::BlockingMode::NonBlockingXCommandsOneResponse;

	if (!waitResponseBeforeSendingAgain)
	{
		m_commandToSendList.append(command);

		bool lastCommandSentIsBlocking = !m_sentCommandList.isEmpty() && m_sentCommandList.last().getOperationMode().blockingMode() == SerialOperationMode::BlockingMode::Blocking;
		if (m_commandToSendList.size() == 1 && !lastCommandSentIsBlocking) {
			nextCommandReady = true;
		}
		if (m_commandToSendList.size() >= m_maxSendBufferSize || m_sentCommandList.size() >= m_maxSendBufferSize) {
			bufferFilled = true;
		}
	}

	m_commandsToSendMutex.unlock();
	m_sentCommandsMutex.unlock();

	if (nextCommandReady)		emit nextCommandReadyToSend();
	if (bufferFilled)			emit commandBufferFilled();  // TODO : intercept signal.
}

void QSerialBuffer::writeResponse(const QByteArray& response)
{
	bool bufferFilled = false;

	m_responsesMutex.lock();

	m_responseBuffer.append(response);

	if (m_responseBuffer.size() >= m_maxResponseBufferSize)
	{
		bufferFilled = true;
	}

	m_responsesMutex.unlock();

	if (bufferFilled) emit commandBufferFilled();  // TODO : intercept signal.
}

void QSerialBuffer::handleSentCommandToSend()
{
	bool nextCommandReady = false;

	m_commandsToSendMutex.lock();
	m_sentCommandsMutex.lock();

	const SerialCommand commandToSend = m_commandToSendList.constFirst();
	const SerialOperationMode::BlockingMode & blockingMode = commandToSend.getOperationMode().blockingMode();

	QList<SerialCommand>::iterator sentCmdIterator = m_sentCommandList.begin();
	while (sentCmdIterator != m_sentCommandList.end())
	{
		SerialCommand &command = *sentCmdIterator;
		// Push mode
		if (command.getOperationMode().fluxMode() == SerialOperationMode::FluxMode::Push)
		{
			if (command.stopsPushMode(commandToSend))
			{
				sentCmdIterator = m_sentCommandList.erase(sentCmdIterator);
			}
		}
		++sentCmdIterator;
	}
	if (blockingMode == SerialOperationMode::BlockingMode::NonBlockingNoResponse)
	{
		m_commandToSendList.removeFirst();
		if (!m_commandToSendList.isEmpty())
		{
			nextCommandReady = true;
		}
	}
	else if (
		blockingMode == SerialOperationMode::BlockingMode::NonBlockingXCommandsXResponses
		|| blockingMode == SerialOperationMode::BlockingMode::NonBlockingXCommandsOneResponse)
	{
		m_sentCommandList.append(m_commandToSendList.takeFirst());
		if (!m_commandToSendList.isEmpty())
		{
			nextCommandReady = true;
		}
	}
	else if (blockingMode == SerialOperationMode::BlockingMode::Blocking)
	{
		m_sentCommandList.append(m_commandToSendList.takeFirst());
	}

	m_commandsToSendMutex.unlock();
	m_sentCommandsMutex.unlock();

	if (nextCommandReady) emit nextCommandReadyToSend();
}
