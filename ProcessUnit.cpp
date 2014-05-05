/*
 * ProcessChamber.cpp
 *
 *  Created on: 2014Äê2ÔÂ20ÈÕ
 *      Author: acm
 */

#include "Event.h"
#include "ProcessUnit.h"
#include "Parameters.h"
#include "Data.h"
#include "WaferManager.h"

ProcessUnit::ProcessUnit(int id, const std::string& name) :
		SmartUnit(id, name), m_dirty_flag(true), m_load_unload_count(0)
{
}

ProcessUnit::~ProcessUnit()
{
}

void ProcessUnit::Initialize()
{
	//base class initialize
	SmartUnit::Initialize();

	if(Data::diPrcCbDoorClose == 0 || Data::diPrcCbLidLeftClose == 0 || Data::diPrcCbLidRightClose == 0)
	{
		m_dirty_flag = false;
	}
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

void ProcessUnit::OnAbort()
{
	if(m_task.command == COMMAND_LOAD || m_task.command == COMMAND_UNLOAD)
	{
		m_load_unload_count = 0;
	}
}

bool ProcessUnit::OnlinePrecheck()
{
	return true;
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
	case COMMAND_PINUP:
		OnPinUp();
		break;
	case COMMAND_PINDOWN:
		OnPinDown();
		break;
	case COMMAND_ROTATE_FORWARD:
		OnRotateForward();
		break;
	case COMMAND_ROTATE_BACKWARD:
		OnRotateBackward();
		break;
	case COMMAND_PUMP:
		OnPump();
		break;
	case COMMAND_VENT:
		OnVent();
		break;
	case COMMAND_PURGE:
		OnPurge();
		break;
	case COMMAND_TURNON_HEATER:
		OnTurnOnHeater();
		break;
	case COMMAND_TURNOFF_HEATER:
		OnTurnOffHeater();
		break;
	case COMMAND_OPEN_DOOR:
		OnOpenDoor();
		break;
	case COMMAND_CLOSE_DOOR:
		OnCloseDoor();
		break;
	default:
		;
	}
}

bool ProcessUnit::OnHome()
{
	if(Data::diPrcCbDoorClose == 0)
	{
		OnCloseDoor();
	}

	if(Data::diWaferPickDown == 0)
	{
		OnPinDown();
	}

	NEW_UNIT_STEP("home", false)
		ADD_STEP_COMMAND([&]()
		{	Data::aoAxisControl = AxisHoming;
			Data::doAxisExecute = (Data::doAxisExecute ? 0 : 1);})
		ADD_STEP_WAIT_CONDITION([&]()->bool
		{	return Data::diAxisNotMoving == 1 && Data::diAxisMoving == 0;},
			Parameters::HomingTimeout * 1000,
			[&](){	EVT::HomingTimeout.Report();})
	END_UNIT_STEP

	OnPinUp();
	OnPinDown();

	return true;
}

void ProcessUnit::create_wafer(int unit, unsigned short slot)
{
	if(Data::LoadUnloadSkip)
		return;

	WaferSize wfs;
	switch(Parameters::WaferSize)
	{
	case 100:
		wfs = WaferSize_100mm;
		break;
	case 150:
		wfs = WaferSize_150mm;
		break;
	case 200:
		wfs = WaferSize_200mm;
		break;
	case 300:
		wfs = WaferSize_300mm;
		break;
	default:
		EVT::UnknownWaferSize.Report();
		return;
	}

	WaferManager::Instance().CreateWafer(unit, slot, Data::WaferBatchID, wfs);
}

bool ProcessUnit::OnLoad()
{
	float pos[3];
	pos[0] = Parameters::ChuckPos1;
	pos[1] = Parameters::ChuckPos2;
	pos[2] = Parameters::ChuckPos3;

	if(!OnOpenDoor())
	{
		return false;
	}

	std::stringstream ss;
	for(int i=2; i>=0; i--)
	{
		ss.str("");
		ss<<"load wafer "<<i;

		float position = pos[i];
		NEW_UNIT_STEP(ss.str(), false)
			auto f1 = [&, position]()
			{	Data::aoAxisPosition = position;
				Data::aoAxisControl = AxisMoveAbsolute;
				Data::doAxisExecute = (Data::doAxisExecute ? 0 : 1);};
			ADD_STEP_COMMAND(f1)
			ADD_STEP_WAIT(1000)
			ADD_STEP_WAIT_CONDITION([&]()
			{	return Data::diReachPosition == 1;},
				1000*Parameters::RotateTimeout,
				[position](){	EVT::RotateTimeout.Report(position);})
			ADD_STEP_COMMAND([&](){Data::LoadUnloadState = 1;})
			ADD_STEP_WAIT_CONDITION([&]()
			{	return Data::LoadUnloadOK == 1;}, UINT_MAX,
				[&](){EVT::LoadUnloadTimeout.Report();})
			ADD_STEP_COMMAND([&]()
			{	Data::LoadUnloadOK = 0;
				Data::LoadUnloadState = 0;})
			auto f2 = [this, i](){create_wafer(m_id, i);};
			ADD_STEP_COMMAND(f2)
			ADD_STEP_COMMAND([this](){++m_load_unload_count;})
		END_UNIT_STEP
	}

	OnCloseDoor();

	return true;
}

void ProcessUnit::remove_wafer(int unit, unsigned short slot)
{
	if(Data::LoadUnloadSkip)
		return;

	WaferManager::Instance().RemoveWafer(unit, slot);
}

bool ProcessUnit::OnUnload()
{
	float pos[3];
	pos[0] = Parameters::ChuckPos1;
	pos[1] = Parameters::ChuckPos2;
	pos[2] = Parameters::ChuckPos3;

	if(!OnOpenDoor())
	{
		return false;
	}

	std::stringstream ss;
	for(int i=0; i<3; i++)
	{
		ss.str("");
		ss<<"unload wafer "<<i;

		float position = pos[i];
		NEW_UNIT_STEP(ss.str(), false)
			auto f1 = [&, position]()
			{	Data::aoAxisPosition = position;
				Data::aoAxisControl = AxisMoveAbsolute;
				Data::doAxisExecute = (Data::doAxisExecute ? 0 : 1);};
			ADD_STEP_COMMAND(f1)
			ADD_STEP_WAIT(1000)
			ADD_STEP_WAIT_CONDITION([&]()
			{	return Data::diReachPosition == 1;},
				1000*Parameters::RotateTimeout,
				[position](){	EVT::RotateTimeout.Report(position);})
			ADD_STEP_COMMAND([&](){Data::LoadUnloadState = 1;})
			ADD_STEP_WAIT_CONDITION([&]()
			{	return Data::LoadUnloadOK == 1;}, UINT_MAX,
				[&](){EVT::LoadUnloadTimeout.Report();})
			ADD_STEP_COMMAND([&]()
			{	Data::LoadUnloadOK = 0;
				Data::LoadUnloadState = 0;})
			auto f2 = [this, i](){remove_wafer(m_id, i);};
			ADD_STEP_COMMAND(f2);
			ADD_STEP_COMMAND([this](){--m_load_unload_count;})
		END_UNIT_STEP
	}

	return true;
}

bool ProcessUnit::OnProcess()
{
	NEW_UNIT_STEP("process", false)
		ADD_STEP_COMMAND([]()
		{	std::cout<<"process command."<<std::endl;})
	END_UNIT_STEP

	return true;
}

bool ProcessUnit::OnClean()
{
	return true;
}

bool ProcessUnit::OnPinUp()
{
	NEW_UNIT_STEP("pin up", false)
		ADD_STEP_COMMAND([&]()
		{	Data::doPinDownVal = 0;
			Data::doPinUpVal = 1;})
		ADD_STEP_WAIT_CONDITION([&]()->bool
		{	return Data::diWaferPickUp == 1 && Data::diWaferPickDown == 0;},
			Parameters::WaferPinTimeout * 1000,
			[&](){	EVT::PinUpDownTimeout.Report("up");})
	END_UNIT_STEP

	return true;
}

bool ProcessUnit::OnPinDown()
{
	NEW_UNIT_STEP("pin down", false)
		ADD_STEP_COMMAND([&]()
		{	Data::doPinDownVal = 1;
			Data::doPinUpVal = 0;})
		ADD_STEP_WAIT_CONDITION([&]()->bool
		{	return Data::diWaferPickUp == 0 && Data::diWaferPickDown == 1;},
			Parameters::WaferPinTimeout * 1000,
			[&](){	EVT::PinUpDownTimeout.Report("down");})
	END_UNIT_STEP

	return true;
}

float ProcessUnit::get_next_position()
{
	float pos[3];
	pos[0] = Parameters::ChuckPos1;
	pos[1] = Parameters::ChuckPos2;
	pos[2] = Parameters::ChuckPos3;

	float current_pos = Data::aiActualPosition;
	unsigned int i=0;
	for(i=0; i<3; i++)
	{
		if(current_pos < pos[i])
			break;
	}

	return pos[i%3];
}

bool ProcessUnit::OnRotateForward()
{
	float next_pos = get_next_position();
	NEW_UNIT_STEP("rotate forward", true)
		auto f = [&, next_pos]()
		{	Data::aoAxisPosition = next_pos;
			Data::aoAxisControl = AxisMoveAbsolute;
			Data::doAxisExecute = (Data::doAxisExecute ? 0 : 1);};
		ADD_STEP_COMMAND(f)
		ADD_STEP_WAIT(1000)
		ADD_STEP_WAIT_CONDITION([&]()->bool
		{	return Data::diReachPosition == 1;},
			1000*Parameters::RotateTimeout,
			[next_pos](){	EVT::RotateTimeout.Report(next_pos);})
	END_UNIT_STEP

	return true;
}

float ProcessUnit::get_last_position()
{
	float pos[3];
	pos[0] = Parameters::ChuckPos1;
	pos[1] = Parameters::ChuckPos2;
	pos[2] = Parameters::ChuckPos3;

	float current_pos = Data::aiActualPosition;
	unsigned int i=0;
	for(i=0; i<3; i++)
	{
		if(current_pos < pos[i])
			break;
	}

	return pos[(i+3-1)%3];
}

bool ProcessUnit::OnRotateBackward()
{
	float last_pos = get_last_position();
	NEW_UNIT_STEP("rotate backward", true)
		auto f = [&, last_pos]()
		{	Data::aoAxisPosition = last_pos;
			Data::aoAxisControl = AxisMoveAbsolute;
			Data::doAxisExecute = (Data::doAxisExecute ? 0 : 1);};
		ADD_STEP_COMMAND(f)
		ADD_STEP_WAIT(1000)
		ADD_STEP_WAIT_CONDITION([&]()->bool
		{	return Data::diReachPosition == 1;},
			1000*Parameters::RotateTimeout,
			[last_pos](){	EVT::RotateTimeout.Report(last_pos);})
	END_UNIT_STEP

	return true;
}

bool ProcessUnit::OnPump()
{
	if(Data::diPrcCbLidLeftClose == 0 || Data::diPrcCbLidRightClose == 0)
	{
		EVT::GenericWarning.Report("Chamber lid isn't closed, pumping is aborted.");
		return false;
	}

	if(Data::diPrcCbDoorClose == 0)
	{
		OnCloseDoor();
	}

	NEW_UNIT_STEP("open apc", true)
		ADD_STEP_COMMAND([&]()
		{	Data::aoAPCPosition = 100;
			Data::aoAPCControlMode = PositionMode;})
	END_UNIT_STEP

	if(Data::doEnableVPump == 0)
	{
		NEW_UNIT_STEP("turn on pump", true)
			ADD_STEP_COMMAND([&]()
			{	Data::doVacFastProcCbVal = 0;
				Data::doVacSlowProcCbVal = 0;
				Data::doEnableVPump = 1;})
			ADD_STEP_WAIT(5000)
			ADD_STEP_WAIT_CONDITION([&]()->bool
			{	return Data::diVPumpWarning == 0 && Data::diVPumpAlarm == 0;},
				1000,
				[&](){	EVT::PumpError.Report();})
		END_UNIT_STEP
	}

	if(Data::aiProcChamPressure > Parameters::FastSlowSwitchPressure)
	{
		NEW_UNIT_STEP("slow pump", true)
			ADD_STEP_COMMAND([&]()
			{	Data::doVacFastProcCbVal = 0;
				Data::doVacSlowProcCbVal = 1;})
			auto condition_function = [&](){return Data::aiProcChamPressure < Parameters::FastSlowSwitchPressure;};
			auto event_function = [&](){EVT::PumpTimeout.Report<float, float>(Data::aiProcChamPressure, Parameters::FastSlowSwitchPressure);};
			ADD_STEP_WAIT_CONDITION(condition_function,	1000*Parameters::SlowPumpTimeout, event_function);
		END_UNIT_STEP
	}

	NEW_UNIT_STEP("fast pump", true)
		ADD_STEP_COMMAND([&]()
		{	Data::doVacFastProcCbVal = 1;
			Data::doVacSlowProcCbVal = 0;})
		auto condition_function = [&](){return Data::aiProcChamPressure < Parameters::PumpDownTargetPressure;};
		auto event_function = [&](){EVT::PumpTimeout.Report<float, float>(Data::aiProcChamPressure, Parameters::PumpDownTargetPressure);};
		ADD_STEP_WAIT_CONDITION(condition_function,	1000*Parameters::FastPumpTimeout, event_function);
	END_UNIT_STEP

	return true;
}

bool ProcessUnit::OnVent()
{
	if(Data::aiProcChamPressure > Parameters::ATMPressure)
	{
		return true;
	}

	if(m_dirty_flag)
	{
		OnPurge();
		//EVT::GenericWarning.Report("Chamber is not clean, gate valve can't be opened.");
		return false;
	}
//
//	NEW_UNIT_STEP(vent, true)
//		ADD_STEP_COMMAND([&]()
//		{	Data::doVacFastProcCbVal = 0;
//			Data::doVacSlowProcCbVal = 0;
//			Data::doExpCbSupplyCbVal = 0;})
//		ADD_STEP_WAIT_CONDITION([&]()->bool
//		{	return Data::aiProcChamPressure < Parameters::PumpDownTargetPressure;},
//			1000*Parameters::FastPumpTimeout,
//			[&](){	EVT::PumpTimeout.Report(Data::aiProcChamPressure, Parameters::PumpDownTargetPressure);})
//	END_UNIT_STEP

	return true;
}

bool ProcessUnit::OnPurge()
{
	return true;
}

bool ProcessUnit::OnTurnOnHeater()
{
	NEW_UNIT_STEP("turn on heater", true)
		ADD_STEP_COMMAND([&]()
		{	Data::aoBodyHTTempSet = Parameters::BodyTemp;
			Data::aoLidHTTempSet = Parameters::LidTemp;
			Data::aoChuckHTTempSet = Parameters::ChuckTemp;
			Data::doBodyHTEnable = 1;
			Data::doLidHTEnable = 1;
			Data::doChuckHTEnable = 1;})
		ADD_STEP_WAIT_CONDITION([&]()->bool
		{	return Data::diBodyHTPowRdy == 1 && Data::diLidHTPowRdy == 1 && Data::diChuckHTPowRdy == 1;},
			2000,
			[&](){	EVT::TurnOnHeaterTimeout.Report();})
	END_UNIT_STEP

	return true;
}

bool ProcessUnit::OnTurnOffHeater()
{
	NEW_UNIT_STEP("turn on heater", false)
		ADD_STEP_COMMAND([&]()
		{	Data::doBodyHTEnable = 0;
			Data::doLidHTEnable = 0;
			Data::doChuckHTEnable = 0;})
	END_UNIT_STEP

	return true;
}

bool ProcessUnit::OnOpenDoor()
{
//	if(Data::diPrcCbDoorOpen == 1 && Data::diPrcCbDoorClose == 0)
//	{
//		return true;
//	}

	if(Data::aiProcChamPressure < Parameters::ATMPressure)
	{
		EVT::GenericWarning.Report("Chamber is not ATM, gate valve can't be opened.");
		return false;
	}

	if(m_dirty_flag)
	{
		EVT::GenericWarning.Report("Chamber is not clean, gate valve can't be opened.");
		return false;
	}

	NEW_UNIT_STEP("open door", true)
		ADD_STEP_COMMAND([&]()
		{	Data::doCbGateVal = 1;})
		ADD_STEP_WAIT_CONDITION([&]()->bool
		{	return Data::diPrcCbDoorOpen == 1 && Data::diPrcCbDoorClose == 0;},
			1000*Parameters::GateValveTimeout,
			[&](){	EVT::GateValveTimeout.Report();})
	END_UNIT_STEP

	return true;
}

bool ProcessUnit::OnCloseDoor()
{
//	if(Data::diPrcCbDoorOpen == 0 && Data::diPrcCbDoorClose == 1)
//	{
//		return true;
//	}

	NEW_UNIT_STEP("close door", true)
		ADD_STEP_COMMAND([&]()
		{	Data::doCbGateVal = 0;})
		ADD_STEP_WAIT_CONDITION([&]()->bool
		{	return Data::diPrcCbDoorOpen == 0 && Data::diPrcCbDoorClose == 1;},
			1000*Parameters::GateValveTimeout,
			[&](){	EVT::GateValveTimeout.Report();})
	END_UNIT_STEP

	return true;
}
