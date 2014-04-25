/*
 * ProcessChamber.cpp
 *
 *  Created on: 2014Äê2ÔÂ20ÈÕ
 *      Author: acm
 */

#include "Event.h"
#include "ProcessUnit.h"
#include "Parameters.h"

ProcessUnit::ProcessUnit(int id, const std::string& name) :
		SmartUnit(id, name)
{
}

ProcessUnit::~ProcessUnit()
{
}

void ProcessUnit::Initialize()
{
	//base class initialize
	SmartUnit::Initialize();

	//initialize hardware parameters
}

void ProcessUnit::Terminate()
{
	//terminate

	//base class terminate
	SmartUnit::Terminate();
}

UnitTask ProcessUnit::GetNextTask()
{
	UnitTask last_task = (m_task.command == COMMAND_NONE) ? m_last_task : m_task;
	if (last_task.command == COMMAND_NONE)
		return UnitTask{COMMAND_HOME, 0, 0};
	else if (last_task.command == COMMAND_HOME)
		return UnitTask{COMMAND_LOAD, 0, 0};
	else if (last_task.command == COMMAND_LOAD)
		return UnitTask{COMMAND_PROCESS, 0, 0};
	else if (last_task.command == COMMAND_PROCESS)
		return UnitTask{COMMAND_UNLOAD, 0, 0};
	else if (last_task.command == COMMAND_UNLOAD)
		return UnitTask{COMMAND_CLEAN, 0, 0};
	else if (last_task.command == COMMAND_CLEAN)
		return UnitTask{COMMAND_LOAD, 0, 0};

	return UnitTask{COMMAND_NONE, 0, 0};
}

void ProcessUnit::UpdateUnitInfo()
{
}

void ProcessUnit::SafeHandle()
{
	//do something to insure safety
}

void ProcessUnit::Notify(const std::string& msg)
{
	EVT::GenericInfo.Report(msg);
}

void ProcessUnit::TranslateTask(const UnitTask& task)
{
	switch (task.command)
	{
	case COMMAND_HOME:
		OnHome();
		break;
	case COMMAND_LOAD:
		OnLoad();
		break;
	case COMMAND_PROCESS:
		OnProcess();
		break;
	case COMMAND_UNLOAD:
		OnUnload();
		break;
	case COMMAND_CLEAN:
		OnClean();
		break;
	default:
		;
	}
}

void ProcessUnit::OnHome()
{
	NEW_UNIT_STEP(home, false)
		ADD_STEP_COMMAND([]()
		{	std::cout<<"home command."<<std::endl;})
		ADD_STEP_WAIT(3000)
		ADD_STEP_COMMAND([]()
		{	std::cout<<"second command."<<std::endl;})
	END_UNIT_STEP
}

void ProcessUnit::OnLoad()
{
	NEW_UNIT_STEP(load, false)
		ADD_STEP_COMMAND([]()
		{	std::cout<<"load command."<<std::endl;})
	END_UNIT_STEP
}

void ProcessUnit::OnUnload()
{
	NEW_UNIT_STEP(unload, false)
		ADD_STEP_COMMAND([]()
		{	std::cout<<"unload command."<<std::endl;})
	END_UNIT_STEP
}

void ProcessUnit::OnProcess()
{
	NEW_UNIT_STEP(process, false)
		ADD_STEP_COMMAND([]()
		{	std::cout<<"process command."<<std::endl;})
	END_UNIT_STEP
}

void ProcessUnit::OnClean()
{
	NEW_UNIT_STEP(clean, false)
		ADD_STEP_COMMAND([]()
		{	std::cout<<"clean command."<<std::endl;})
//		ADD_STEP_WAIT_CONDITION([=]()->bool
//		{	return Parameters::RotateSpeed>200;}, 2000, [=]()
//		{	EVT::WiferBroken.Report("A3");})
	END_UNIT_STEP
}
