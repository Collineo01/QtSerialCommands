#include "QSerialBuffer.h"
#include <QMutex>

QSerialBuffer::QSerialBuffer(int sendBufferSize, int responsesBufferSize, QObject * parent) :
	QObject(parent),
	m_nbOfReadyCommands{ 0 },
	m_maxSendBufferSize{ sendBufferSize },
	m_maxResponseBufferSize{ responsesBufferSize }
{
}

QSerialBuffer::~QSerialBuffer()
{
}

void QSerialBuffer::removeMatchedCommand(const SerialCommand * command)
{
}

void QSerialBuffer::removeMatchedResponse(const QByteArray & matchedResponse)
{
	m_mutex.lock();
	m_responseBuffer.remove(m_responseBuffer.indexOf(matchedResponse), matchedResponse.length());
	m_mutex.unlock();
}

void QSerialBuffer::removeNextCommandToSend()
{
	m_mutex.lock();
	m_commandToSendList.removeFirst();
	m_mutex.unlock();
}

void QSerialBuffer::moveNextCmdToSentBuffer()
{
	m_mutex.lock();
	m_sentCommandList.append(m_commandToSendList.takeFirst());
	m_mutex.unlock();
}

QList<SerialCommand>::iterator QSerialBuffer::sentCommandsBegin()
{
	m_mutex.lock();
	QList<SerialCommand>::iterator iterator = m_sentCommandList.begin();
	m_mutex.unlock();

	return iterator;
}

QList<SerialCommand>::iterator QSerialBuffer::sentCommandsEnd()
{
	m_mutex.lock();
	QList<SerialCommand>::iterator iterator = m_sentCommandList.end();
	m_mutex.unlock();

	return iterator;
}

QList<SerialCommand>::iterator QSerialBuffer::eraseSentCommand(QList<SerialCommand>::iterator it)
{
	m_mutex.lock();
	QList<SerialCommand>::iterator iterator = m_sentCommandList.erase(it);
	m_mutex.unlock();

	return iterator;
}

int QSerialBuffer::sentCommandListSize()
{
	m_mutex.lock();
	int size = m_sentCommandList.size();
	m_mutex.unlock();

	return size;
}

void QSerialBuffer::clearBuffersNow()
{
	m_mutex.lock();
	m_commandToSendList.clear();
	m_sentCommandList.clear();
	m_responseBuffer.clear();
	m_mutex.unlock();
}

SerialCommand QSerialBuffer::takeLastCommandSent()
{
	m_mutex.lock();
	SerialCommand command = m_sentCommandList.takeLast();
	m_mutex.unlock();

	return command;
}

QByteArray QSerialBuffer::getResponseBuffer()
{
	m_mutex.lock();
	QByteArray responses = m_responseBuffer;
	m_mutex.unlock();

	return responses;
}

SerialCommand QSerialBuffer::getNextCommandToSend() const
{
	return m_commandToSendList.constFirst();
}

bool QSerialBuffer::isResponseBufferEmpty() const
{
	return m_responseBuffer.isEmpty();
}

void QSerialBuffer::writeCommand(const SerialCommand & command)
{
	m_mutex.lock();

	const bool commandIsInBuffer = m_commandToSendList.contains(command) || m_sentCommandList.contains(command);
	const bool waitResponseBeforeSendingAgain = command.getOperationMode().blockingMode() == SerialOperationMode::BlockingMode::NonBlockingXCommandsOneResponse;

	if (!(commandIsInBuffer && waitResponseBeforeSendingAgain))
	{
		m_commandToSendList.append(command);

		bool lastCommandSentIsNotBlocking = m_sentCommandList.isEmpty() || m_sentCommandList.last().getOperationMode().blockingMode() != SerialOperationMode::BlockingMode::Blocking;
		if (m_commandToSendList.size() == 1 && lastCommandSentIsNotBlocking) {
			emit commandIsReadyToSend(command);
		}
		if (m_commandToSendList.size() >= m_maxSendBufferSize || m_sentCommandList.size() >= m_maxSendBufferSize) {
			emit commandBufferFilled();  // TODO : intercept signal.
		}
	}

	m_mutex.unlock();
}

void QSerialBuffer::writeResponse(const QByteArray& response)
{
	m_mutex.lock();

	if (m_responseBuffer.size() >= m_maxResponseBufferSize)
	{
		emit responseBufferFilled(); // TODO : intercept signal.
	}
	else
	{
		m_responseBuffer.append(response);
	}

	m_mutex.unlock();
}
