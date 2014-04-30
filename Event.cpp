/*
 * Event.cpp
 *
 *  Created on: 2014Äê2ÔÂ20ÈÕ
 *      Author: acm
 */

#include "SystemEvent.h"

namespace EVT
{
	SystemEvent GenericInfo(1001, EVENT_LEVEL_INFO, "%s");
	SystemEvent GenericWarning(1002, EVENT_LEVEL_WARNING, "%s");
	SystemEvent GenericError(1003, EVENT_LEVEL_ERROR, "%s");

	SystemEvent ValueOutOfRange(1004, EVENT_LEVEL_WARNING, "New value %f is out of range [%f, %f] for %s.");
	SystemEvent LoadRecipeFailed(1006, EVENT_LEVEL_WARNING, "Failed to load recipe %s.");
	SystemEvent PinUpDownTimeout(1008, EVENT_LEVEL_ERROR, "Pin %s timeout.");
	SystemEvent TurnOnHeaterTimeout(1010, EVENT_LEVEL_ERROR, "Turn on heater timeout.");
	SystemEvent RotateTimeout(1012, EVENT_LEVEL_ERROR, "Rotate to %f degrees timeout.");
	SystemEvent HomingTimeout(1013, EVENT_LEVEL_ERROR, "Homing chuck timeout.");
	SystemEvent GateValveTimeout(1014, EVENT_LEVEL_ERROR, "Open/Close gate valve timeout.");
	SystemEvent PumpTimeout(1016, EVENT_LEVEL_ERROR, "Pumping timeout from %f (torr) to %f (torr).");
	SystemEvent PumpError(1018, EVENT_LEVEL_ERROR, "Pump warning/alarm.");
}


