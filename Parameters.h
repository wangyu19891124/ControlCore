#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include "ParameterItem.h"

namespace Parameters
{

//define all needed parameters here
extern ParameterItem<int> RotateSpeed;
extern ParameterItem<int> H2Flow;
extern ParameterItem<double> PlateTemperature;
extern ParameterItem<std::string> EfemIP;

}

#endif
