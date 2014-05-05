#pragma once

#include "SystemEvent.h"

namespace EVT
{

extern SystemEvent GenericInfo;
extern SystemEvent GenericWarning;
extern SystemEvent GenericError;

extern SystemEvent ValueOutOfRange;
extern SystemEvent LoadRecipeFailed;
extern SystemEvent PinUpDownTimeout;
extern SystemEvent TurnOnHeaterTimeout;
extern SystemEvent RotateTimeout;
extern SystemEvent HomingTimeout;
extern SystemEvent GateValveTimeout;
extern SystemEvent PumpTimeout;
extern SystemEvent PumpError;
extern SystemEvent UnknownWaferSize;
extern SystemEvent LoadUnloadTimeout;

}
