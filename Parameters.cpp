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
ParameterItem<float> VaporizerTC1(1, "VaporizerTC1", "Temperature", "Vaporizer TC1", 0, 200, 20, "Cels");
ParameterItem<float> TC1WarnRange(2, "TC1WarnRange", "Temperature", "Warning range of TC1 temperature", 0, 200, 20, "Cels");
ParameterItem<float> TC1AlarmRange(3, "TC1AlarmRange", "Temperature", "Alarm range of TC1 temperature", 0, 200, 20, "Cels");
ParameterItem<float> VaporizerTC2(4, "VaporizerTC2", "Temperature", "Vaporizer TC2", 0, 200, 20, "Cels");
ParameterItem<float> TC2WarnRange(5, "TC2WarnRange", "Temperature", "Warning range of TC2 temperature", 0, 200, 20, "Cels");
ParameterItem<float> TC2AlarmRange(6, "TC2AlarmRange", "Temperature", "Alarm range of TC2 temperature", 0, 200, 20, "Cels");
ParameterItem<float> LidTemperature(7, "LidTemperature", "Temperature", "Chamber lid temperature", 0, 200, 20, "Cels");
ParameterItem<float> LidTempWarnRange(8, "LidTempWarnRange", "Temperature", "Warning range of chamber lid temperature", 0, 200, 20, "Cels");
ParameterItem<float> LidTempAlarmRange(9, "LidTempAlarmRange", "Temperature", "Alarm range of chamber lid temperature", 0, 200, 20, "Cels");
ParameterItem<float> ChuckTemperature(10, "ChuckTemperature", "Temperature", "Chamber chuck temperature", 0, 200, 20, "Cels");
ParameterItem<float> ChuckTempWarnRange(11, "ChuckTempWarnRange", "Temperature", "Warning range of chamber chuck temperature", 0, 200, 20, "Cels");
ParameterItem<float> ChuckTempAlarmRange(12, "ChuckTempAlarmRange", "Temperature", "Alarm range of chamber chuck temperature", 0, 200, 20, "Cels");
ParameterItem<float> ChamberTemperature(13, "ChamberTemperature", "Temperature", "Chamber temperature", 0, 200, 20, "Cels");
ParameterItem<float> ChamberTempWarnRange(14, "ChamberTempWarnRange", "Temperature", "Warning range of chamber temperature", 0, 200, 20, "Cels");
ParameterItem<float> ChamberTempAlarmRange(15, "ChamberTempAlarmRange", "Temperature", "Alarm range of chamber temperature", 0, 200, 20, "Cels");

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

//Process
ParameterItem<float> ChamCommPressure(3001,"ChamCommPressure","Pressure","ChamberCommPressure setting value",0,500,100,"torr");
ParameterItem<float> ChamCommPressureWarn(3002,"ChamCommPressureWarn","Pressure","ChamberCommPressure warning value",0,500,300,"torr");
ParameterItem<float> ChamCommPressureAlarm(3003,"ChamCommPressureAlarm","Pressure","ChamberCommPressure alarm value",0,500,400,"torr");
ParameterItem<float> WaferPinUpTime(3004,"WaferPinUpTime","Time","Pin up lift Time Out value",0,100,10,"s");
ParameterItem<float> PostEtchN2Flow(3005,"PostEtchN2Flow","PostEtch","Post Etch N2 Flow Setting",0,800,300,"sccm");
ParameterItem<float> PostEtchN2Pressure(3006,"PostEtchN2Pressure","PostEtch","Post Etch N2 Presssure",0,800,200,"torr");
ParameterItem<float> PostEtchN2LowerPre(3007,"PostEtchN2LowerPre","PostEtch","Post Etch N2 Purge lower Pressure",0,800,100,"torr");
ParameterItem<int> PostEtchPurgeTimes(3008,"PostEtchPurgeTimes","PostEtch","Post Etch Purge Times",0,100,10,"times");
ParameterItem<int> PostEtchKeepTime(3009,"PostEtchKeepTime","PostEtch","Post Etch Purge Keep Time",0,300,10,"s");

}



