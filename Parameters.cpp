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

//position
ParameterItem<float> ChuckPos1(1001,"WaferPos1","Position","wafer1 in chuck position",0,360,0,"deg");
ParameterItem<float> ChuckPos2(1002,"WaferPos2","Position","wafer2 in chuck position",0,360,120,"deg");
ParameterItem<float> ChuckPos3(1003,"WaferPos3","Position","wafer3 in chuck position",0,360,240,"deg");
ParameterItem<float> ChuckHomeDegree(1004,"HomeDegree","Degree","chuck home degree",0,360,100,"deg");
ParameterItem<float> ChuckSpinDegree(1005,"SpinDegree","Degree","chuck spin degree",0,360,100,"deg");

//Flow
ParameterItem<float> EtohFlow(2001,"EtohFlowSet","Flow","Etoh flow value",0,1000,300,"sccm");
ParameterItem<float> EtohFlowWarn(2002,"EtohFlowWarn","Flow","Etoh flow warn value",0,1000,500,"sccm");
ParameterItem<float> EtohFlowAlarm(2003,"EtohFlowAlm","Flow","Etoh flow alarm value",0,1000,800,"sccm");
ParameterItem<float> HFFlow(2004,"HFFlowSet","Flow","HF flow value",0,1000,300,"sccm");
ParameterItem<float> HFFlowWarn(2005,"HFFlowWarn","Flow","HF flow warn value",0,1000,500,"sccm");
ParameterItem<float> HFFlowAlarm(2006,"HFFlowAlm","Flow","HF flow alarm value",0,1000,800,"sccm");
ParameterItem<float> CAN2Flow(2007,"CAN2FlowSet","Flow","CAN2 flow value",0,1000,300,"sccm");
ParameterItem<float> CAN2FlowWarn(2008,"CAN2FlowWarn","Flow","CAN2 flow warn value",0,1000,500,"sccm");
ParameterItem<float> CAN2FlowAlarm(2009,"CAN2FlowAlm","Flow","CAN2 flow alarm value",0,1000,800,"sccm");
ParameterItem<float> PGN2Flow(2010,"PGN2FlowSet","Flow","PGN2 flow value",0,1000,300,"sccm");
ParameterItem<float> PGN2FlowWarn(2011,"PGN2FlowWarn","Flow","PGN2 flow warn value",0,1000,500,"sccm");
ParameterItem<float> PGN2FlowAlarm(2012,"PGN2FlowAlm","Flow","PGN2 flow alarm value",0,1000,800,"sccm");

//Process
ParameterItem<float> ChamCommPressure(3001,"ChamCommPre","Pressure","ChamberCommPressure setting value",0,500,100,"torr");
ParameterItem<float> ChamCommPressureWarn(3002,"ChamCommPreWarn","Pressure","ChamberCommPressure warning value",0,500,300,"torr");
ParameterItem<float> ChamCommPressureAlm(3003,"ChamCommPreAlm","Pressure","ChamberCommPressure alarm value",0,500,400,"torr");
ParameterItem<float> WaferPinUpTime(3004,"WaferPinTime","Time","Pin up lift Time Out value",0,100,10,"s");
ParameterItem<float> PostEtchN2Flow(3005,"N2Flow","PostEtch","Post Etch N2 Flow Setting",0,800,300,"sccm");
ParameterItem<float> PostEtchN2Pressure(3006,"N2Pressure","PostEtch","Post Etch N2 Presssure",0,800,200,"torr");
ParameterItem<float> PostEtchN2LowerPre(3007,"N2PreLower","PostEtch","Post Etch N2 Purge lower Pressure",0,800,100,"torr");
ParameterItem<int> PostEtchPGNum(3008,"PurgeNum","PostEtch","Post Etch Purge Times",0,100,10,"num");
ParameterItem<int> PostEtchKeepTime(3009,"PurgeTime","PostEtch","Post Etch Purge Keep Time",0,300,10,"s");


ParameterItem<int> RotateSpeed(3010, "RotateSpeed", "Motion/Motor", "speed setpoint of rotor.", 0, 2000, 50, "rpm");
ParameterItem<int> H2Flow(3011, "H2Flow", "Motion/Motor", "H2 flow rate.", 0, 500, 300, "sccm");
ParameterItem<double> PlateTemperature(3012, "PlateTemperature", "Heater/Plate", "temperature of plate.", -10.0, 200, 20, "Cels");
ParameterItem<std::string> EfemIP(3013, "IP", "System/Efem", "IP address of EFEM.", "192.168.0.100");

}



