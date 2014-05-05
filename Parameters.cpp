/*
 * Parameter.cpp
 *
 *  Created on: 2014Äê2ÔÂ20ÈÕ
 *      Author: acm
 */

#include "ParameterItem.h"

namespace Parameters
{

//define all needed parameters here
//temperature
ParameterItem<float> LidTemp(20, "LidTemp", "Heater", "Chamber lid temperature", 0, 200, 20, "Cels");
ParameterItem<float> BodyTemp(21, "BodyTemp", "Heater", "Chamber body temperature", 0, 200, 20, "Cels");
ParameterItem<float> ChuckTemp(22, "ChuckTemp", "Heater", "Chamber chuck temperature", 0, 200, 20, "Cels");
ParameterItem<float> TempWarnOffset(25, "TempWarnOffset", "Heater", "Relative temperature offset of warning to setting value.", 0, 50, 10, "Cels");
ParameterItem<float> TempAlarmOffset(26, "TempAlarmOffset", "Heater", "Relative temperature offset of alarm to setting value.", 0, 50, 20, "Cels");


//Chuck position
ParameterItem<float> ChuckPos1(1001,"ChuckPos1","Chuck","chuck position1",0,360,0,"deg");
ParameterItem<float> ChuckPos2(1002,"ChuckPos2","Chuck","chuck position2",0,360,120,"deg");
ParameterItem<float> ChuckPos3(1003,"ChuckPos3","Chuck","chuck position3",0,360,240,"deg");
ParameterItem<float> ChuckPatrolStart(1004,"ChuckPatrolStart","Chuck","chuck patrol start degree",0,360,0,"deg");
ParameterItem<float> ChuckPatrolEnd(1005,"ChuckPatrolEnd","Chuck","chuck patrol end degree",0,360,360,"deg");


//Flow
ParameterItem<unsigned> EtOHFlow(2001,"EtOHFlow","Flow","Etoh flow value",0,1000,300,"sccm");
ParameterItem<unsigned> EtOHFlowWarn(2002,"EtOHFlowWarn","Flow","Etoh flow warn value",0,1000,500,"sccm");
ParameterItem<unsigned> EtOHFlowAlarm(2003,"EtOHFlowAlarm","Flow","Etoh flow alarm value",0,1000,800,"sccm");
ParameterItem<unsigned> HFFlow(2004,"HFFlow","Flow","HF flow value",0,1000,300,"sccm");
ParameterItem<unsigned> HFFlowWarn(2005,"HFFlowWarn","Flow","HF flow warn value",0,1000,500,"sccm");
ParameterItem<unsigned> HFFlowAlarm(2006,"HFFlowAlarm","Flow","HF flow alarm value",0,1000,800,"sccm");
ParameterItem<unsigned> N2Flow(2007,"N2Flow","Flow","N2 flow value",0,1000,300,"sccm");
ParameterItem<unsigned> N2FlowWarn(2008,"N2FlowWarn","Flow","N2 flow warn value",0,1000,500,"sccm");
ParameterItem<unsigned> N2FlowAlarm(2009,"N2FlowAlarm","Flow","N2 flow alarm value",0,1000,800,"sccm");
ParameterItem<unsigned> PurgeN2Flow(2010,"PurgeN2Flow","Flow","Purge N2 flow value",0,1000,300,"sccm");
ParameterItem<unsigned> PurgeN2FlowWarn(2011,"PurgeN2FlowWarn","Flow","Purge N2 flow warn value",0,1000,500,"sccm");
ParameterItem<unsigned> PurgeN2FlowAlarm(2012,"PurgeN2FlowAlarm","Flow","Purge N2 flow alarm value",0,1000,800,"sccm");


//Pressure
ParameterItem<float> ATMPressure(3001,"ATMPressure","Pressure","ATM pressure",600,800,730,"torr");
ParameterItem<float> VacuumPressure(3002,"VacuumPressure","Pressure","Vacuum pressure",0,100,10,"torr");


//Purge
ParameterItem<float> N2PurgeFlow(4000,"N2PurgeFlow","Purge","N2 purge flowrate.",0,5000,1000,"sccm");
ParameterItem<unsigned> PurgeRepeatTimes(4002,"PurgeRepeatTimes","Purge","Repeat times for purge.",0,20,3,"times");
ParameterItem<float> PurgeTargetPressure(4003,"PurgeTargetPressure","Purge","Purge target pressure.",0,500,400,"torr");
ParameterItem<unsigned> FlushTime(4004,"FlushTime","Purge","Flush time after purge.",0,100,30,"s");
ParameterItem<unsigned> FlushFlowrate(4005,"FlushFlowrate","Purge","Flush flowrate of N2.",0,5000,1000,"sccm");
ParameterItem<unsigned> PurgeHoldTime(4006,"PurgeHoldTime","Purge","Hold time after reaching PurgeTargetPressure.",0,100,5,"s");
ParameterItem<unsigned> PumpHoldTime(4007,"PumpHoldTime","Purge","Hold time after reaching PumpDownTargetPressure.",0,100,5,"s");


//Valve
ParameterItem<unsigned> GateValveTimeout(5000,"GateValveTimeout","Valve","Open/close gate valve timeout.",0,100,10,"s");


//Motion
ParameterItem<unsigned> WaferPinTimeout(6004,"WaferPinTimeout","Motion","Pin up/down timeout.",0,100,10,"s");
ParameterItem<unsigned> RotateTimeout(6014,"RotateTimeout","Motion","Chuck rotation timeout.",0,100,20,"s");
ParameterItem<unsigned> HomingTimeout(6015,"HomingTimeout","Motion","Chuck rotation timeout.",0,100,60,"s");


//Pump
ParameterItem<float> FastSlowSwitchPressure(7000,"FastSlowSwitchPressure","Pump","Turn on fast valve and close slow valve when pressure lower than this value.",0,700,400,"torr");
ParameterItem<float> PumpDownTargetPressure(7001,"PumpDownTargetPressure","Pump","Pump down procedure finished when pressure lower than this value.",0,100,0.1,"torr");
ParameterItem<unsigned> SlowPumpTimeout(7003,"SlowPumpTimeout","Pump","Pump timeout from ATM to FastSlowSwitchPressure.",0,100,60,"s");
ParameterItem<unsigned> FastPumpTimeout(7004,"FastPumpTimeout","Pump","Pump timeout from FastSlowSwitchPressure to Vacuum.",0,100,60,"s");


//Wafer
ParameterItem<unsigned> WaferSize(8000,"WaferSize","Wafer","Wafer size(150/200/300mm).",0,1000,300,"mm");

}



