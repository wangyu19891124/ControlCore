/*
 * Event.cpp
 *
 *  Created on: 2014��2��20��
 *      Author: acm
 */

#include "SystemEvent.h"

namespace EVT
{
	SystemEvent ValueOutOfRange(1004, EVENT_LEVEL_WARNING, "New value %f is out of range [%f, %f] for %s.");
	SystemEvent LoadRecipeFailed(1006, EVENT_LEVEL_WARNING, "Failed to load recipe %s.");
}


