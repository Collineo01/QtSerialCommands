/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/

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
