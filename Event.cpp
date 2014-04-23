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
	SystemEvent GasLeak(1002, EVENT_LEVEL_FATAL, "Gas %s leak in %s.");
	SystemEvent ValueOutOfRange(1004, EVENT_LEVEL_WARNING, "New value %f is out of range [%f, %f] for %s.");
}


