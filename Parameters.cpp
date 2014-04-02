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
ParameterItem<int> RotateSpeed(1, "RotateSpeed", "Motion/Motor", "speed setpoint of rotor.", 0, 2000, 50, "rpm");
ParameterItem<int> H2Flow(2, "H2Flow", "Motion/Motor", "H2 flow rate.", 0, 500, 300, "L/min");
ParameterItem<double> PlateTemperature(3, "PlateTemperature", "Heater/Plate", "temperature of plate.", -10.0, 200, 20, "¡æ");
ParameterItem<std::string> EfemIP(4, "IP", "System/Efem", "IP address of EFEM.", "192.168.0.100");

}



