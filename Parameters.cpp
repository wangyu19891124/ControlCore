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
ParameterItem<int> RotateSpeed(1, "Motor/RotateSpeed", "speed setpoint of rotor.", 0, 2000, 50, "rpm");
ParameterItem<int> H2Flow(2, "Motor/H2Flow", "H2 flow rate.", 0, 500, 300, "L/min");
ParameterItem<double> PlateTemperature(3, "Plate/PlateTemperature", "temperature of plate.", -10.0, 200, 20, "¡æ");
ParameterItem<std::string> EfemIP(4, "Efem/IP", "IP address of EFEM.", "192.168.0.100");

}



