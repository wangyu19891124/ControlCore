/*
 * Event.cpp
 *
 *  Created on: 2014Äê2ÔÂ20ÈÕ
 *      Author: acm
 */

#include "SystemEvent.h"

namespace EVT
{
	SystemEvent PowerOn(1000, EVENT_LEVEL_INFO, "System power on.");
	SystemEvent WiferBroken(1001, EVENT_LEVEL_ERROR, "Wafer is broken in chamber %s.");
	SystemEvent GasLeak(1002, EVENT_LEVEL_EMERGENCY, "Gas %s leak in chamber %s.");
}


