/*
 * ProcessChamber.cpp
 *
 *  Created on: 2014Äê2ÔÂ20ÈÕ
 *      Author: acm
 */

#include "Event.h"
#include "ProcessChamber.h"
#include "Parameters.h"

ProcessChamber::ProcessChamber(int id) :
		SmartUnit(id)
{
	// TODO Auto-generated constructor stub

}

ProcessChamber::~ProcessChamber()
{
	// TODO Auto-generated destructor stub
}

void ProcessChamber::Initialize()
{
	//initialize

	//base clase initialize
	SmartUnit::Initialize();
}

void ProcessChamber::Terminate()
{
	//base class terminate
	SmartUnit::Terminate();

	//terminate
}

UnitTask ProcessChamber::GetNextTask()
{
	UnitTask last_task = (m_task.type == Task_None) ? m_last_task : m_task;
	if (last_task.type == Task_None)
		return UnitTask{Task_Home, 0, 0};
	else if (last_task.type == Task_Home)
		return UnitTask{Task_Load, 0, 0};
	else if (last_task.type == Task_Load)
		return UnitTask{Task_Process, 0, 0};
	else if (last_task.type == Task_Process)
		return UnitTask{Task_Unload, 0, 0};
	else if (last_task.type == Task_Unload)
		return UnitTask{Task_Clean, 0, 0};
	else if (last_task.type == Task_Clean)
		return UnitTask{Task_Load, 0, 0};

	return UnitTask{Task_None, 0, 0};
}

void ProcessChamber::UpdateUnitInfo()
{
	static int count = 0;
	if(count++%10 == 0)
		std::cout<<"unit state: "<<m_state<<", queue size: "<<m_steps.size()<<"current step: "<<m_cur_step<<std::endl;
}

void ProcessChamber::SafeHandle()
{
	std::cout<<"a~~~o----"<<std::endl;
}

bool ProcessChamber::TranslateTask(const UnitTask& task)
{
	//base
	if (!SmartUnit::TranslateTask(task))
		return false;

	//translate task
	switch (task.type)
	{
	case Task_Home:
		OnHome();
		break;
	case Task_Load:
		OnLoad();
		break;
	case Task_Process:
		OnProcess();
		break;
	case Task_Unload:
		OnUnload();
		break;
	case Task_Clean:
		OnClean();
		break;
	default:
		;
	}

	return true;
}

void ProcessChamber::OnHome()
{
	NEW_UNIT_STEP(home, false)
		ADD_STEP_COMMAND([]()
		{	std::cout<<"home command."<<std::endl;})
		ADD_STEP_WAIT(3000)
		ADD_STEP_COMMAND([]()
		{	std::cout<<"second command."<<std::endl;})
	END_UNIT_STEP
}

void ProcessChamber::OnLoad()
{
	NEW_UNIT_STEP(load, false)
		ADD_STEP_COMMAND([]()
		{	std::cout<<"load command."<<std::endl;})
	END_UNIT_STEP
}

void ProcessChamber::OnUnload()
{
	NEW_UNIT_STEP(unload, false)
		ADD_STEP_COMMAND([]()
		{	std::cout<<"unload command."<<std::endl;})
	END_UNIT_STEP
}

void ProcessChamber::OnProcess()
{
	NEW_UNIT_STEP(process, false)
		ADD_STEP_COMMAND([]()
		{	std::cout<<"process command."<<std::endl;})
	END_UNIT_STEP
}

void ProcessChamber::OnClean()
{
	NEW_UNIT_STEP(clean, false)
		ADD_STEP_COMMAND([]()
		{	std::cout<<"clean command."<<std::endl;})
		ADD_STEP_WAIT_CONDITION([=]()->bool
		{	return Parameters::RotateSpeed>200;}, 2000, [=]()
		{	EVT::WiferBroken.Report("A3");})
	END_UNIT_STEP
}
