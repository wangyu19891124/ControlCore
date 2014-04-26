#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include "ParameterItem.h"

namespace Parameters
{


//temperature
extern ParameterItem<float> VaporizerTC1;
extern ParameterItem<float> TC1WarnRange;
extern ParameterItem<float> TC1AlarmRange;
extern ParameterItem<float> VaporizerTC2;
extern ParameterItem<float> TC2WarnRange;
extern ParameterItem<float> TC2AlarmRange;
extern ParameterItem<float> LidTemperature;
extern ParameterItem<float> LidTempWarnRange;
extern ParameterItem<float> LidTempAlarmRange;
extern ParameterItem<float> ChuckTemperature;
extern ParameterItem<float> ChuckTempWarnRange;
extern ParameterItem<float> ChuckTempAlarmRange;
extern ParameterItem<float> ChamberTemperature;
extern ParameterItem<float> ChamberTempWarnRange;
extern ParameterItem<float> ChamberTempAlarmRange;

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

//Process
extern ParameterItem<float> ChamCommPressure;
extern ParameterItem<float> ChamCommPressureWarn;
extern ParameterItem<float> ChamCommPressureAlarm;
extern ParameterItem<float> WaferPinUpTime;
extern ParameterItem<float> PostEtchN2Flow;
extern ParameterItem<float> PostEtchN2Pressure;
extern ParameterItem<float> PostEtchN2LowerPre;
extern ParameterItem<int> PostEtchPurgeTimes;
extern ParameterItem<int> PostEtchKeepTime;


}

#endif
