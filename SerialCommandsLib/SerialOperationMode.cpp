#include "SerialOperationMode.h"


SerialOperationMode::SerialOperationMode(BlockingMode blockingMode, FluxMode fluxMode)
	: mBlockingMode{ blockingMode }, mFluxMode{ fluxMode }
{
}


SerialOperationMode::SerialOperationMode()
{
}


SerialOperationMode::~SerialOperationMode()
{
}
