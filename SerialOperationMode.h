#pragma once

#include "qtserialcommands_global.h"


/*! \class SerialOperationMode
*/

class QTSERIALCOMMANDS_EXPORT SerialOperationMode
{
public:
	enum class BlockingMode
	{
		// Wait for the response before sending any other getCommand.
		Blocking = 0,

		// Not expecting any response.
		NonBlockingNoResponse = 1,

		// Expecting as many responses as the number of commands sent.
		NonBlockingXCommandsXResponses = 2,

		// Will not send more of the same getCommand before receiving the response (prevents spamming).
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

