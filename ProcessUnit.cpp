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
		SmartUnit(id, name), m_dirty_flag(true)
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

void ProcessUnit::OnHome()
{
	if(Data::diPrcCbDoorClose == 0)
	{
		OnCloseDoor();
	}

	if(Data::diWaferPickDown == 0)
	{
		OnPinDown();
	}

	NEW_UNIT_STEP(home, false)
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
}

void ProcessUnit::OnLoad()
{
}

void ProcessUnit::OnUnload()
{
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
}

void ProcessUnit::OnPinUp()
{
	NEW_UNIT_STEP(pin_up, false)
		ADD_STEP_COMMAND([&]()
		{	Data::doPinDownVal = 0;
			Data::doPinUpVal = 1;})
		ADD_STEP_WAIT_CONDITION([&]()->bool
		{	return Data::diWaferPickUp == 1 && Data::diWaferPickDown == 0;},
			Parameters::WaferPinTimeout * 1000,
			[&](){	EVT::PinUpDownTimeout.Report("up");})
	END_UNIT_STEP
}

void ProcessUnit::OnPinDown()
{
	NEW_UNIT_STEP(pin_down, false)
		ADD_STEP_COMMAND([&]()
		{	Data::doPinDownVal = 1;
			Data::doPinUpVal = 0;})
		ADD_STEP_WAIT_CONDITION([&]()->bool
		{	return Data::diWaferPickUp == 0 && Data::diWaferPickDown == 1;},
			Parameters::WaferPinTimeout * 1000,
			[&](){	EVT::PinUpDownTimeout.Report("down");})
	END_UNIT_STEP
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

void ProcessUnit::OnRotateForward()
{
	float next_pos = get_next_position();
	NEW_UNIT_STEP(rotate_forward, true)
		ADD_STEP_COMMAND([&]()
		{	Data::aoAxisPosition = next_pos;
			Data::aoAxisControl = AxisMoveAbsolute;
			Data::doAxisExecute = (Data::doAxisExecute ? 0 : 1);})
		ADD_STEP_WAIT(1000)
		ADD_STEP_WAIT_CONDITION([&]()->bool
		{	return Data::diReachPosition == 1;},
			1000*Parameters::RotateTimeout,
			[next_pos](){	EVT::RotateTimeout.Report(next_pos);})
	END_UNIT_STEP
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

void ProcessUnit::OnRotateBackward()
{
	float last_pos = get_last_position();
	NEW_UNIT_STEP(rotate_backward, true)
		ADD_STEP_COMMAND([&]()
		{	Data::aoAxisPosition = last_pos;
			Data::aoAxisControl = AxisMoveAbsolute;
			Data::doAxisExecute = (Data::doAxisExecute ? 0 : 1);})
		ADD_STEP_WAIT(1000)
		ADD_STEP_WAIT_CONDITION([&]()->bool
		{	return Data::diReachPosition == 1;},
			1000*Parameters::RotateTimeout,
			[last_pos](){	EVT::RotateTimeout.Report(last_pos);})
	END_UNIT_STEP
}

void ProcessUnit::OnPump()
{
	if(Data::diPrcCbLidLeftClose == 0 || Data::diPrcCbLidLeftOpen == 1
			|| Data::diPrcCbLidRightClose == 0 || Data::diPrcCbLidRightOpen == 1)
	{
		EVT::GenericWarning.Report("Chamber lid isn't closed, pumping is aborted.");
		return;
	}

	if(Data::diPrcCbDoorClose == 0 || Data::diPrcCbDoorOpen == 1)
	{
		OnCloseDoor();
	}

	NEW_UNIT_STEP(open_apc, true)
		ADD_STEP_COMMAND([&]()
		{	Data::aoAPCPosition = 100;
			Data::aoAPCControlMode = PositionMode;})
	END_UNIT_STEP

	if(Data::doEnableVPump == 0)
	{
		NEW_UNIT_STEP(turnon_pump, true)
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
		NEW_UNIT_STEP(slow_pump, true)
			ADD_STEP_COMMAND([&]()
			{	Data::doVacFastProcCbVal = 0;
				Data::doVacSlowProcCbVal = 1;})
			ADD_STEP_WAIT_CONDITION([&]()->bool
			{	return Data::aiProcChamPressure < Parameters::FastSlowSwitchPressure;},
				1000*Parameters::SlowPumpTimeout,
				[&](){	EVT::PumpTimeout.Report(Data::aiProcChamPressure, Parameters::FastSlowSwitchPressure);})
		END_UNIT_STEP
	}

	NEW_UNIT_STEP(fast_pump, true)
		ADD_STEP_COMMAND([&]()
		{	Data::doVacFastProcCbVal = 1;
			Data::doVacSlowProcCbVal = 0;})
		ADD_STEP_WAIT_CONDITION([&]()->bool
		{	return Data::aiProcChamPressure < Parameters::PumpDownTargetPressure;},
			1000*Parameters::FastPumpTimeout,
			[&](){	EVT::PumpTimeout.Report(Data::aiProcChamPressure, Parameters::PumpDownTargetPressure);})
	END_UNIT_STEP
}

void ProcessUnit::OnVent()
{
	if(Data::aiProcChamPressure > Parameters::ATMPressure)
	{
		return;
	}

	if(m_dirty_flag)
	{
		EVT::GenericWarning.Report("Chamber is not clean, gate valve can't be opened.");
		return;
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

}

void ProcessUnit::OnPurge()
{

}

void ProcessUnit::OnTurnOnHeater()
{
	NEW_UNIT_STEP(turn_on_heater, true)
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
}

void ProcessUnit::OnTurnOffHeater()
{
	NEW_UNIT_STEP(turn_on_heater, false)
		ADD_STEP_COMMAND([&]()
		{	Data::doBodyHTEnable = 0;
			Data::doLidHTEnable = 0;
			Data::doChuckHTEnable = 0;})
	END_UNIT_STEP
}

void ProcessUnit::OnOpenDoor()
{
	if(Data::aiProcChamPressure < Parameters::ATMPressure)
	{
		EVT::GenericWarning.Report("Chamber is not ATM, gate valve can't be opened.");
		return;
	}

	if(m_dirty_flag)
	{
		EVT::GenericWarning.Report("Chamber is not clean, gate valve can't be opened.");
		return;
	}

	NEW_UNIT_STEP(open_door, true)
		ADD_STEP_COMMAND([&]()
		{	Data::doCbGateVal = 1;})
		ADD_STEP_WAIT_CONDITION([&]()->bool
		{	return Data::diPrcCbDoorOpen == 1 && Data::diPrcCbDoorClose == 0;},
			1000*Parameters::GateValveTimeout,
			[&](){	EVT::GateValveTimeout.Report();})
	END_UNIT_STEP
}

void ProcessUnit::OnCloseDoor()
{

	NEW_UNIT_STEP(close_door, true)
		ADD_STEP_COMMAND([&]()
		{	Data::doCbGateVal = 0;})
		ADD_STEP_WAIT_CONDITION([&]()->bool
		{	return Data::diPrcCbDoorOpen == 0 && Data::diPrcCbDoorClose == 1;},
			1000*Parameters::GateValveTimeout,
			[&](){	EVT::GateValveTimeout.Report();})
	END_UNIT_STEP
}
