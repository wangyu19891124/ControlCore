#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include "ParameterItem.h"

namespace Parameters
{

//define all needed parameters here
//temperature
extern ParameterItem<float> LidTemp;
extern ParameterItem<float> BodyTemp;
extern ParameterItem<float> ChuckTemp;
extern ParameterItem<float> TempWarnOffset;
extern ParameterItem<float> TempAlarmOffset;


//Chuck position
extern ParameterItem<float> ChuckPos1;
extern ParameterItem<float> ChuckPos2;
extern ParameterItem<float> ChuckPos3;
extern ParameterItem<float> ChuckPatrolStart;
extern ParameterItem<float> ChuckPatrolEnd;


//Flow
extern ParameterItem<unsigned> EtOHFlow;
extern ParameterItem<unsigned> EtOHFlowWarn;
extern ParameterItem<unsigned> EtOHFlowAlarm;
extern ParameterItem<unsigned> HFFlow;
extern ParameterItem<unsigned> HFFlowWarn;
extern ParameterItem<unsigned> HFFlowAlarm;
extern ParameterItem<unsigned> N2Flow;
extern ParameterItem<unsigned> N2FlowWarn;
extern ParameterItem<unsigned> N2FlowAlarm;
extern ParameterItem<unsigned> PurgeN2Flow;
extern ParameterItem<unsigned> PurgeN2FlowWarn;
extern ParameterItem<unsigned> PurgeN2FlowAlarm;


//Pressure
extern ParameterItem<float> ATMPressure;
extern ParameterItem<float> VacuumPressure;
extern ParameterItem<float> PressureDiffAllowance;

//Purge
extern ParameterItem<unsigned> N2PurgeFlow;
extern ParameterItem<unsigned> PurgeRepeatTimes;
extern ParameterItem<float> PurgeTargetPressure;
extern ParameterItem<unsigned> FlushTime;
extern ParameterItem<unsigned> FlushFlowrate;
extern ParameterItem<unsigned> PurgeHoldTime;
extern ParameterItem<unsigned> PumpHoldTime;
extern ParameterItem<unsigned> HFPurgeFlow;
extern ParameterItem<unsigned> EtOHPurgeFlow;

//Valve
extern ParameterItem<unsigned> GateValveTimeout;


//Motion
extern ParameterItem<unsigned> WaferPinTimeout;
extern ParameterItem<unsigned> RotateTimeout;
extern ParameterItem<unsigned> HomingTimeout;

//Pump
extern ParameterItem<float> FastSlowSwitchPressure;
extern ParameterItem<float> PumpDownTargetPressure;
extern ParameterItem<unsigned> SlowPumpTimeout;
extern ParameterItem<unsigned> FastPumpTimeout;
extern ParameterItem<unsigned> PumpExpTimeout;

//Wafer
extern ParameterItem<unsigned> WaferSize;

//LeakCheck
extern ParameterItem<float> LeakCheckPressure;
extern ParameterItem<unsigned> LeakCheckPumpHoldTime;
extern ParameterItem<unsigned> LeakCheckTime;
extern ParameterItem<float> LeakCheckThreshold;

}

#endif
