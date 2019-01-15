#pragma once




/*! \class SerialOperationMode
*
*	\brief Conteneur pour les modes d'opération d'une commande
*
*/

class SerialOperationMode
{
public:
	enum class BlockingMode
	{
		// Wait for the response before sending any other command.
		Blocking = 0,

		// Not expecting any response.
		NonBlockingNoResponse = 1,

		// Expecting as many responses as the number of commands sent.
		NonBlockingXCommandsXResponses = 2,

		// Will not send more of the same command before receiving the response (prevents spamming).
		NonBlockingXCommandsOneResponse = 3
	};

	enum class FluxMode { Pull = 0, Push = 1 };

	SerialOperationMode(BlockingMode blockingMode, FluxMode fluxMode);
	SerialOperationMode();
	~SerialOperationMode();

	FluxMode fluxMode() const { return m_fluxMode; }
	BlockingMode blockingMode() const { return m_blockingMode; }


private:
	BlockingMode m_blockingMode;
	FluxMode m_fluxMode;
};

