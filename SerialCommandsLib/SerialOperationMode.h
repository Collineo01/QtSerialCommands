#pragma once

#include "serialcommandslib_global.h"


/*! \class SerialOperationMode
*
*	\brief Conteneur pour les modes d'opération d'une commande
*
*/

class SERIALCOMMANDSLIB_EXPORT SerialOperationMode
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
		NonBlockingWaitResponse = 3
	};

	enum class FluxMode { Pull = 0, Push = 1 };

	SerialOperationMode(BlockingMode blockingMode, FluxMode fluxMode);
	SerialOperationMode();
	~SerialOperationMode();

	FluxMode fluxMode() { return mFluxMode; }
	BlockingMode blockingMode() { return mBlockingMode; }


private:
	BlockingMode mBlockingMode;
	FluxMode mFluxMode;
};

