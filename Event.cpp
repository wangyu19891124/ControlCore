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
}


