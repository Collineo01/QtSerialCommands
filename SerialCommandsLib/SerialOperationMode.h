/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/

/*! \class SerialOperationMode
*
*	\brief Conteneur pour les modes d'opération d'une commande
*
*/


#ifndef SERIALOPERATIONMODE_H
#define SERIALOPERATIONMODE_H

#include "serialcommandslib_global.h"

class SERIALCOMMANDSLIB_EXPORT SerialOperationMode
{
public:
	enum class BlockingMode { Blocking = 0, NonBlockingNoResponse = 1, NonBlockingWithResponse = 2 };
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

#endif
