/*
 * UnitManager.cpp
 *
 *  Created on: 2014��4��24��
 *      Author: Administrator
 */

#include "UnitManager.h"
#include "ProcessUnit.h"

void UnitManager::Initialize()
{
	m_units[0] = boost::shared_ptr<SmartUnit>(new ProcessUnit(0, "ProcessUnit"));
	m_units[0]->Initialize();
}

void UnitManager::Terminate()
{
	m_units[0]->Terminate();
	m_units.clear();
}


void UnitManager::Invoke(int unit, int cmd, unsigned param1, unsigned param2)
{
	boost::shared_ptr<SmartUnit> unit_ptr = m_units[unit];
	if(unit_ptr)
	{
		unit_ptr->Invoke(cmd, param1, param2);
	}
}
