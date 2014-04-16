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
ParameterItem<float> VaporizerTC1(1, "VaporizerTC1", "Temperature", "Vaporizer TC1", 0, 200, 20, "¡æ");
ParameterItem<float> TC1WarnRange(2, "TC1WarnRange", "Temperature", "Warning range of TC1 temperature", 0, 200, 20, "¡æ");
ParameterItem<float> TC1AlarmRange(3, "TC1AlarmRange", "Temperature", "Alarm range of TC1 temperature", 0, 200, 20, "¡æ");
ParameterItem<float> VaporizerTC2(4, "VaporizerTC2", "Temperature", "Vaporizer TC2", 0, 200, 20, "¡æ");
ParameterItem<float> TC2WarnRange(5, "TC2WarnRange", "Temperature", "Warning range of TC2 temperature", 0, 200, 20, "¡æ");
ParameterItem<float> TC2AlarmRange(6, "TC2AlarmRange", "Temperature", "Alarm range of TC2 temperature", 0, 200, 20, "¡æ");
ParameterItem<float> LidTemperature(7, "LidTemperature", "Temperature", "Chamber lid temperature", 0, 200, 20, "¡æ");
ParameterItem<float> LidTempWarnRange(8, "LidTempWarnRange", "Temperature", "Warning range of chamber lid temperature", 0, 200, 20, "¡æ");
ParameterItem<float> LidTempAlarmRange(9, "LidTempAlarmRange", "Temperature", "Alarm range of chamber lid temperature", 0, 200, 20, "¡æ");
ParameterItem<float> ChuckTemperature(10, "ChuckTemperature", "Temperature", "Chamber chuck temperature", 0, 200, 20, "¡æ");
ParameterItem<float> ChuckTempWarnRange(11, "ChuckTempWarnRange", "Temperature", "Warning range of chamber chuck temperature", 0, 200, 20, "¡æ");
ParameterItem<float> ChuckTempAlarmRange(12, "ChuckTempAlarmRange", "Temperature", "Alarm range of chamber chuck temperature", 0, 200, 20, "¡æ");
ParameterItem<float> ChamberTemperature(13, "ChamberTemperature", "Temperature", "Chamber temperature", 0, 200, 20, "¡æ");
ParameterItem<float> ChamberTempWarnRange(14, "ChamberTempWarnRange", "Temperature", "Warning range of chamber temperature", 0, 200, 20, "¡æ");
ParameterItem<float> ChamberTempAlarmRange(15, "ChamberTempAlarmRange", "Temperature", "Alarm range of chamber temperature", 0, 200, 20, "¡æ");

//position

ParameterItem<int> RotateSpeed(1, "RotateSpeed", "Motion/Motor", "speed setpoint of rotor.", 0, 2000, 50, "rpm");
ParameterItem<int> H2Flow(2, "H2Flow", "Motion/Motor", "H2 flow rate.", 0, 500, 300, "L/min");
ParameterItem<double> PlateTemperature(3, "PlateTemperature", "Heater/Plate", "temperature of plate.", -10.0, 200, 20, "¡æ");
ParameterItem<std::string> EfemIP(4, "IP", "System/Efem", "IP address of EFEM.", "192.168.0.100");

}



