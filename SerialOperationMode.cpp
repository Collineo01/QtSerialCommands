#include "SerialOperationMode.h"


SerialOperationMode::SerialOperationMode(BlockingMode blockingMode, FluxMode fluxMode)
	: m_blockingMode{ blockingMode }, m_fluxMode{ fluxMode }
{
}


SerialOperationMode::SerialOperationMode()
{
}


SerialOperationMode::~SerialOperationMode()
{
}
