/*
 * ProcessChamber.cpp
 *
 *  Created on: 2014��2��20��
 *      Author: acm
 */

#include "Event.h"
#include "ProcessUnit.h"
#include "Parameters.h"
#include "Data.h"
#include "WaferManager.h"

using boost::chrono;

ProcessUnit::ProcessUnit(int id, const std::string& name) :
		SmartUnit(id, name), m_proc_dirty_flag(true), m_exp_dirty_flag(true), m_load_unload_count(0),
		m_leak_check_init_pressure(0)
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
		m_proc_dirty_flag = false;
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

void ProcessUnit::ErrorHandle()
{
	//do something to insure safety and change state information
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
		OnPump(task.para1);
		break;
	case COMMAND_VENT:
		OnVent(task.para1);
		break;
	case COMMAND_PURGE:
		OnPurge(task.para1);
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
	case COMMAND_LEAKCHECK:
		OnLeakCheck(task.para1);
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

	NEW_UNIT_STEP("home", false)
		ADD_STEP_COMMAND([&]()
		{	Data::aoAxisControl = AxisControl_Homing;
			Data::doAxisExecute = (Data::doAxisExecute ? 0 : 1);})
		ADD_STEP_WAIT_CONDITION([&]()->bool
		{	return Data::diAxisNotMoving == 1 && Data::diAxisMoving == 0;},
			Parameters::HomingTimeout * 1000,
			[&](){	EVT::HomingTimeout.Report();})
	END_UNIT_STEP

	OnPinUp();
	OnPinDown();
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

void ProcessUnit::OnLoad()
{
	float pos[3];
	pos[0] = Parameters::ChuckPos1;
	pos[1] = Parameters::ChuckPos2;
	pos[2] = Parameters::ChuckPos3;

	if(!OnOpenDoor())
	{
		return;
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
				Data::aoAxisControl = AxisControl_Absolute;
				Data::doAxisExecute = (Data::doAxisExecute ? 0 : 1);};
			ADD_STEP_COMMAND(f1)
			ADD_STEP_WAIT(1000)
			ADD_STEP_WAIT_CONDITION([&]()
			{	return Data::diReachPosition == 1;},
				Parameters::RotateTimeout,
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
}

void ProcessUnit::remove_wafer(int unit, unsigned short slot)
{
	if(Data::LoadUnloadSkip)
		return;

	WaferManager::Instance().RemoveWafer(unit, slot);
}

void ProcessUnit::OnUnload()
{
	float pos[3];
	pos[0] = Parameters::ChuckPos1;
	pos[1] = Parameters::ChuckPos2;
	pos[2] = Parameters::ChuckPos3;

	if(!OnOpenDoor())
	{
		return;
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
				Data::aoAxisControl = AxisControl_Absolute;
				Data::doAxisExecute = (Data::doAxisExecute ? 0 : 1);};
			ADD_STEP_COMMAND(f1)
			ADD_STEP_WAIT(1000)
			ADD_STEP_WAIT_CONDITION([&]()
			{	return Data::diReachPosition == 1;},
				Parameters::RotateTimeout,
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
}

void ProcessUnit::process_recipe_step(unsigned index, const RecipeStep& recipe_step)
{
	Data::CurrentStepTime = recipe_step.Duration();
	Data::CurrentStep = index + 1;
	Data::StepElapseTime = 0;
	m_step_start_time = boost::chrono::system_clock::now();
	if (recipe_step.Mode() == APCMode_Position)
	{
		Data::aoAPCControlMode = APCControl_Position;
		Data::aoAPCPosition = recipe_step.Position();
		//Monitor::Instance().Disable("ProcessPressure");
	}
	else
	{
		Data::aoAPCControlMode = APCControl_Pressure;
		float pressure = recipe_step.Pressure();
		float pres_warn_offset = Parameters::PressureWarnOffset;
		float pres_alarm_offset = Parameters::PressureAlarmOffset;
		Data::aoAPCPressure = pressure;
		Monitor::Instance().Reset("ProcessPressure", pressure, pres_warn_offset, pres_alarm_offset);
	}
	unsigned short rpm = recipe_step.RotateSpeed();
	if (rpm > 0)
	{
		Data::aoAxisVelocity = rpm * 360 / 60;
		Data::aoAxisControl = AxisControl_Velocity;
	}
	else
	{
		Data::aoAxisControl = AxisControl_Stop;
	}
	Data::doAxisExecute = (Data::doAxisExecute ? 0 : 1);

	float flowrate = 0;
	float flow_warn_offset = 0;
	float flow_alarm_offset = 0;
	BypassMode bps_mode = recipe_step.HFBypass();
	if (bps_mode == BypassMode_None)
	{
		Data::doExpCbHFInletVal = 0;
		Data::doVaHFValve = 0;
		Data::aoHFFlowSetpoint = 0;
	}
	else
	{
		if (bps_mode == BypassMode_Bypass)
		{
			Data::doExpCbHFInletVal = 0;
			Data::doVaHFValve = 1;
		}
		else
		{
			Data::doExpCbHFInletVal = 1;
			Data::doVaHFValve = 0;
		}

		flowrate = recipe_step.HFFlowrate();
		flow_warn_offset = 0.01 * flowrate * Parameters::FlowWarnProportion;
		flow_warn_offset = std::max<float>(Parameters::FlowWarnMinimum, flow_warn_offset);
		flow_alarm_offset = 0.01 * flowrate * Parameters::FlowAlarmProportion;
		flow_alarm_offset = std::max<float>(Parameters::FlowAlarmMinimum, flow_alarm_offset);
		Data::aoHFFlowSetpoint = flowrate;
		Monitor::Instance().Reset("HFFlow", flowrate, flow_warn_offset, flow_alarm_offset);
	}
	Data::doHFMFCVal1 = 1;
	Data::doHFMFCVal2 = 1;

	bps_mode = recipe_step.EtOHBypass();
	if (bps_mode == BypassMode_None)
	{
		Data::doExpCbVacIPASupply = 0;
		Data::doVaVapValve = 0;
		Data::aoEtOHFlowSetpoint = 0;
	}
	else
	{
		if (bps_mode == BypassMode_Bypass)
		{
			Data::doExpCbVacIPASupply = 0;
			Data::doVaVapValve = 1;
		}
		else
		{
			Data::doExpCbVacIPASupply = 1;
			Data::doVaVapValve = 0;
		}
		flowrate = recipe_step.EtOHFlowrate();
		flow_warn_offset = 0.01 * flowrate * Parameters::FlowWarnProportion;
		flow_warn_offset = std::max<float>(Parameters::FlowWarnMinimum, flow_warn_offset);
		flow_alarm_offset = 0.01 * flowrate * Parameters::FlowAlarmProportion;
		flow_alarm_offset = std::max<float>(Parameters::FlowAlarmMinimum, flow_alarm_offset);
		Data::aoEtOHFlowSetpoint = flowrate;
		Monitor::Instance().Reset("EtOHFlow", flowrate, flow_warn_offset, flow_alarm_offset);
	}
	Data::doAlcMFCVal1 = 1;
	Data::doAlcMFCVal2 = 1;

	Data::doN2MFCVal1 = 1;
	Data::doN2MFCVal2 = 1;
	flowrate = recipe_step.N2Flowrate();
	flow_warn_offset = 0.01 * flowrate * Parameters::FlowWarnProportion;
	flow_warn_offset = std::max<float>(Parameters::FlowWarnMinimum, flow_warn_offset);
	flow_alarm_offset = 0.01 * flowrate * Parameters::FlowAlarmProportion;
	flow_alarm_offset = std::max<float>(Parameters::FlowAlarmMinimum, flow_alarm_offset);
	Data::aoN2FlowSetpoint = flowrate;
	Monitor::Instance().Reset("N2Flow", flowrate, flow_warn_offset, flow_alarm_offset);

	Data::doPurgeN2MFCVal1 = 1;
	Data::doPurgeN2MFCVal2 = 1;
	flowrate = recipe_step.N2PurgeFlowrate();
	flow_warn_offset = 0.01 * flowrate * Parameters::FlowWarnProportion;
	flow_warn_offset = std::max<float>(Parameters::FlowWarnMinimum, flow_warn_offset);
	flow_alarm_offset = 0.01 * flowrate * Parameters::FlowAlarmProportion;
	flow_alarm_offset = std::max<float>(Parameters::FlowAlarmMinimum, flow_alarm_offset);
	Data::aoPurgeN2FlowSetpoint = flowrate;
	Monitor::Instance().Reset("N2PurgeFlow", flowrate, flow_warn_offset, flow_alarm_offset);
}

void ProcessUnit::OnProcess()
{
	if(Data::aiProcChamPressure > Parameters::VacuumPressure)
	{
		EVT::ChamberNotVacuum.Report("Process");
		return;
	}

	if(Data::aiExpChamPressure > Parameters::VacuumPressure)
	{
		EVT::ChamberNotVacuum.Report("Expansion");
		return;
	}

	Recipe rcp;
	RecipeManager::Instance().GetRecipe(rcp);
	unsigned steps = rcp.TotalStep();
	unsigned recipe_duration = rcp.Duration();

	NEW_UNIT_STEP("prepare process", false)
		ADD_STEP_COMMAND([]()
		{	Data::doExpCbVapVacValve = 0;
			Data::doN2SupplyProcVal = 0;
			Data::doAlcTankOpen = 1;
			Data::doVaSupplyIPAValve = 1;
			Data::doHFFacSupplyVal = 1;
			Data::doVapBypassValve = 0;
			Data::doVapSupplyN2Valve = 1;
			Data::doVacSlowProcCbVal = 0;
			Data::doVacFastProcCbVal = 1;
			Data::doExpCbSupplyCbVal = 1;
			Data::RecipeElapseTime = 0;
			Data::doAlcMFCVal3 = 0;
			Data::doHFMFCVal3 = 0;
			Data::doExpCbVacValve = 1;
		})
		auto f = [this, steps, recipe_duration]()
		{	m_recipe_start_time = boost::chrono::system_clock::now();
			Data::TotalSteps = steps;
			Data::RecipeTotalTime = recipe_duration;
		};
		ADD_STEP_COMMAND(f)
	END_UNIT_STEP

	std::stringstream ss;
	for(unsigned i=0; i<steps; i++)
	{
		const RecipeStep& rcp_step = rcp.Step(i);
		unsigned step_time = rcp_step.Duration();
		ss.str("");
		ss<<"process step "<<(i+1);
		NEW_UNIT_STEP(ss.str(), false)
			auto f = [&, i, rcp_step](){ process_recipe_step(i, rcp_step);};
			ADD_STEP_COMMAND(f)
			auto condition = [&]()
			{
				auto dur = duration_cast<chrono::seconds>(chrono::system_clock::now() - m_step_start_time);
				Data::StepElapseTime = dur.count();
				dur = boost::chrono::duration_cast<chrono::seconds>(chrono::system_clock::now() - m_recipe_start_time);
				Data::RecipeElapseTime = dur.count();

				return !Monitor::Instance().HasAlarm();
			};
			ADD_STEP_EXPECT(condition, step_time, [&](){EVT::ProcessAlarm.Report();})
			ADD_STEP_COMMAND([&](){Monitor::Instance().DisableAll();})
		END_UNIT_STEP
	}

	NEW_UNIT_STEP("process finish", false)
		auto f = [&, steps, recipe_duration]()
		{	Data::doHFFacSupplyVal = 0;
			Data::doVapSupplyN2Valve = 0;
			Data::doAlcMFCVal1 = 0;
			Data::doAlcMFCVal2 = 0;
			Data::aoEtOHFlowSetpoint = 0;
			Data::doHFMFCVal1 = 0;
			Data::doHFMFCVal2 = 0;
			Data::aoHFFlowSetpoint = 0;
			Data::doN2MFCVal1 = 0;
			Data::doN2MFCVal2 = 0;
			Data::aoN2FlowSetpoint = 0;
			Data::doPurgeN2MFCVal1 = 0;
			Data::doPurgeN2MFCVal2 = 0;
			Data::aoPurgeN2FlowSetpoint = 0;
			Data::CurrentStep = steps;
			Data::RecipeElapseTime = recipe_duration;
			Data::aoAPCControlMode = APCControl_Position;
			Data::aoAPCPosition = 100;
		};
		ADD_STEP_COMMAND(f)
	END_UNIT_STEP
}

void ProcessUnit::OnLeakCheck(unsigned param)
{
	switch(param)
	{
	case 0:
		OnProcChamberLeakCheck();
		break;
	case 1:
		OnExpChamberLeakCheck();
		break;
	default:
		;
	}
}

void ProcessUnit::OnProcChamberLeakCheck()
{
	if(Data::diPrcCbLidLeftClose == 0 || Data::diPrcCbLidRightClose == 0)
	{
		EVT::GenericWarning.Report("Chamber lid isn't closed, leak check is aborted.");
		return;
	}

	NEW_UNIT_STEP("initialize state", true)
		ADD_STEP_COMMAND([&]()
		{	Data::LeakCheckState = 1;
			Data::LeakRate = 0;
			Data::LeakCheckStateText = "Testing";
			Data::LeakCheckResult = "Testing";})
	END_UNIT_STEP

	if(Data::diPrcCbDoorClose == 0)
	{
		OnCloseDoor();
	}

	NEW_UNIT_STEP("prepare pump", true)
		ADD_STEP_COMMAND([&]()
		{	Data::doExpCbSupplyCbVal = 0;
			Data::doN2SupplyProcVal = 0;
			Data::aoAPCPosition = 100;
			Data::aoAPCControlMode = APCControl_Position;})
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
			float pressure1 = Data::aiProcChamPressure;
			float pressure2 = Parameters::FastSlowSwitchPressure;
			auto event_function = [=](){EVT::PumpTimeout.Report<float, float>(pressure1, pressure2);};
			ADD_STEP_WAIT_CONDITION(condition_function,	Parameters::SlowPumpTimeout, event_function);
		END_UNIT_STEP
	}

	NEW_UNIT_STEP("fast pump", true)
		ADD_STEP_COMMAND([&]()
		{	Data::doVacFastProcCbVal = 1;
			Data::doVacSlowProcCbVal = 0;})
		auto condition_function = [&](){return Data::aiProcChamPressure < Parameters::LeakCheckPressure;};
		float pressure1 = Data::aiProcChamPressure;
		float pressure2 = Parameters::LeakCheckPressure;
		auto event_function = [=](){EVT::PumpTimeout.Report<float, float>(pressure1, pressure2);};
		ADD_STEP_WAIT_CONDITION(condition_function,	Parameters::FastPumpTimeout, event_function);
		ADD_STEP_WAIT(Parameters::LeakCheckPumpHoldTime)
	END_UNIT_STEP


	NEW_UNIT_STEP("leak check", true)
		ADD_STEP_COMMAND([&]()
		{	Data::doVacFastProcCbVal = 0;
			m_leak_check_init_pressure = Data::aiProcChamPressure;})
		ADD_STEP_WAIT(Parameters::LeakCheckTime)
		ADD_STEP_COMMAND([&]()
		{	float leak_rate = 60*(Data::aiProcChamPressure - m_leak_check_init_pressure)/Parameters::LeakCheckTime;
			Data::LeakCheckState = 0;
			Data::LeakCheckStateText = "Finish";
			Data::LeakRate = leak_rate;
			if(leak_rate > Parameters::LeakCheckThreshold)
			{
				Data::LeakCheckResult = "FAIL";
			}
			else
			{
				Data::LeakCheckResult = "PASS";
			}
		})
	END_UNIT_STEP
}

void ProcessUnit::OnExpChamberLeakCheck()
{
	NEW_UNIT_STEP("initialize state", true)
		ADD_STEP_COMMAND([&]()
		{	Data::LeakCheckState = 1;
			Data::LeakRate = 0;
			Data::LeakCheckStateText = "Testing";
			Data::LeakCheckResult = "Testing";})
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

	NEW_UNIT_STEP("pump", true)
		ADD_STEP_COMMAND([&]()
		{	Data::doExpCbSupplyCbVal = 0;
			Data::doExpCbVacIPASupply = 0;
			Data::doExpCbHFInletVal = 0;
			Data::doPurgeN2MFCVal1 = 0;
			Data::doPurgeN2MFCVal2 = 0;
			Data::aoPurgeN2FlowSetpoint = 0;
			Data::doVaVapValve = 0;
			Data::doVaHFValve = 0;
			Data::doExpCbVacValve = 1;
			Data::doExpCbVapVacValve = 1;})
		auto condition_function = [&](){return Data::aiExpChamPressure < Parameters::LeakCheckPressure;};
		float pressure1 = Data::aiExpChamPressure;
		float pressure2 = Parameters::LeakCheckPressure;
		auto event_function = [=](){EVT::PumpTimeout.Report<float, float>(pressure1, pressure2);};
		ADD_STEP_WAIT_CONDITION(condition_function,	Parameters::PumpExpTimeout, event_function);
		ADD_STEP_WAIT(Parameters::LeakCheckPumpHoldTime)
	END_UNIT_STEP

	NEW_UNIT_STEP("leak check", true)
		ADD_STEP_COMMAND([&]()
		{	Data::doExpCbVacValve = 0;
			Data::doExpCbVapVacValve = 0;
			m_leak_check_init_pressure = Data::aiExpChamPressure;})
		ADD_STEP_WAIT(Parameters::LeakCheckTime)
		ADD_STEP_COMMAND([&]()
		{	float leak_rate = 60*(Data::aiExpChamPressure - m_leak_check_init_pressure)/Parameters::LeakCheckTime;
			Data::LeakCheckState = 0;
			Data::LeakRate = leak_rate;
			Data::LeakCheckStateText = "Finish";
			if(leak_rate > Parameters::LeakCheckThreshold)
			{
				Data::LeakCheckResult = "FAIL";
			}
			else
			{
				Data::LeakCheckResult = "PASS";
			}
		})
	END_UNIT_STEP
}

void ProcessUnit::OnPinUp()
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
}

void ProcessUnit::OnPinDown()
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
	NEW_UNIT_STEP("rotate forward", true)
		auto f = [&, next_pos]()
		{	Data::aoAxisPosition = next_pos;
			Data::aoAxisControl = AxisControl_Absolute;
			Data::doAxisExecute = (Data::doAxisExecute ? 0 : 1);};
		ADD_STEP_COMMAND(f)
		ADD_STEP_WAIT(1000)
		ADD_STEP_WAIT_CONDITION([&]()->bool
		{	return Data::diReachPosition == 1;},
			Parameters::RotateTimeout,
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
	NEW_UNIT_STEP("rotate backward", true)
		auto f = [&, last_pos]()
		{	Data::aoAxisPosition = last_pos;
			Data::aoAxisControl = AxisControl_Absolute;
			Data::doAxisExecute = (Data::doAxisExecute ? 0 : 1);};
		ADD_STEP_COMMAND(f)
		ADD_STEP_WAIT(1000)
		ADD_STEP_WAIT_CONDITION([&]()->bool
		{	return Data::diReachPosition == 1;},
			Parameters::RotateTimeout,
			[last_pos](){	EVT::RotateTimeout.Report(last_pos);})
	END_UNIT_STEP
}

void ProcessUnit::OnPump(unsigned param)
{
	switch(param)
	{
	case 0:
		OnPumpProcChamber();
		break;
	case 1:
		OnPumpExpChamber();
		break;
	default:
		;
	}
}

bool ProcessUnit::OnPumpProcChamber()
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

	NEW_UNIT_STEP("prepare pump", true)
		ADD_STEP_COMMAND([&]()
		{	Data::doExpCbSupplyCbVal = 0;
			Data::doN2SupplyProcVal = 0;
			Data::aoAPCPosition = 100;
			Data::aoAPCControlMode = APCControl_Position;})
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
			float pressure1 = Data::aiProcChamPressure;
			float pressure2 = Parameters::FastSlowSwitchPressure;
			auto event_function = [=](){EVT::PumpTimeout.Report<float, float>(pressure1, pressure2);};
			ADD_STEP_WAIT_CONDITION(condition_function,	Parameters::SlowPumpTimeout, event_function);
		END_UNIT_STEP
	}

	NEW_UNIT_STEP("fast pump", true)
		ADD_STEP_COMMAND([&]()
		{	Data::doVacFastProcCbVal = 1;
			Data::doVacSlowProcCbVal = 0;})
		auto condition_function = [&](){return Data::aiProcChamPressure < Parameters::PumpDownTargetPressure;};
		float pressure1 = Data::aiProcChamPressure;
		float pressure2 = Parameters::PumpDownTargetPressure;
		auto event_function = [=](){EVT::PumpTimeout.Report<float, float>(pressure1, pressure2);};
		ADD_STEP_WAIT_CONDITION(condition_function,	Parameters::FastPumpTimeout, event_function);
	END_UNIT_STEP


	NEW_UNIT_STEP("finish pump", true)
		ADD_STEP_COMMAND([&]()
		{	float pressure_difference = fabs(Data::aiExpChamPressure - Data::aiProcChamPressure);
			if(pressure_difference < Parameters::PressureDiffAllowance)
			{
				Data::doExpCbSupplyCbVal = 1;
				Data::doExpCbVacValve = 0;
				Data::doExpCbVapVacValve = 0;
			}})
	END_UNIT_STEP

	return true;
}

bool ProcessUnit::OnPumpExpChamber()
{
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

	NEW_UNIT_STEP("pump", true)
		ADD_STEP_COMMAND([&]()
		{	Data::doExpCbSupplyCbVal = 0;
			Data::doExpCbVacIPASupply = 0;
			Data::doExpCbHFInletVal = 0;
			Data::doPurgeN2MFCVal1 = 0;
			Data::doPurgeN2MFCVal2 = 0;
			Data::aoPurgeN2FlowSetpoint = 0;
			Data::doVaVapValve = 0;
			Data::doVaHFValve = 0;
			Data::doExpCbVacValve = 1;
			Data::doExpCbVapVacValve = 1;})
		auto condition_function = [&](){return Data::aiExpChamPressure < Parameters::PumpDownTargetPressure;};
		float pressure1 = Data::aiExpChamPressure;
		float pressure2 = Parameters::PumpDownTargetPressure;
		auto event_function = [=](){EVT::PumpTimeout.Report<float, float>(pressure1, pressure2);};
		ADD_STEP_WAIT_CONDITION(condition_function,	Parameters::PumpExpTimeout, event_function);
	END_UNIT_STEP

	return true;
}

void ProcessUnit::OnVent(unsigned param)
{
	switch(param)
	{
	case 0:
		OnVentProcChamber();
		break;
	case 1:
		OnVentExpChamber();
		break;
	default:
		;
	}
}

bool ProcessUnit::OnVentExpChamber()
{
	if(Data::aiExpChamPressure > Parameters::ATMPressure)
	{
		return true;
	}

	if(m_exp_dirty_flag)
	{
		//OnPurgeProcChamber();
		EVT::ChamberNotClean.Report("Expansion");
		return false;
	}

	NEW_UNIT_STEP("vent", true)
		ADD_STEP_COMMAND([&]()
		{	Data::doExpCbVapVacValve = 0;
			Data::doExpCbSupplyCbVal = 0;
			Data::doExpCbVacIPASupply = 0;
			Data::doExpCbHFInletVal = 0;
			Data::doPurgeN2MFCVal1 = 1;
			Data::doPurgeN2MFCVal2 = 1;
			Data::aoPurgeN2FlowSetpoint = Parameters::ExpVentFlowrate;})
		ADD_STEP_WAIT_CONDITION([&]()->bool
		{	return Data::aiExpChamPressure > Parameters::ATMPressure;},
			Parameters::VentExpTimeout,
			[&](){	EVT::VentTimeout.Report("expansion");})
		ADD_STEP_COMMAND([&]()
		{	Data::doPurgeN2MFCVal1 = 0;
			Data::doPurgeN2MFCVal2 = 0;
			Data::aoPurgeN2FlowSetpoint = 0;})
	END_UNIT_STEP

	return true;
}

bool ProcessUnit::OnVentProcChamber()
{
	if(Data::aiProcChamPressure > Parameters::ATMPressure)
	{
		return true;
	}

	if(m_proc_dirty_flag)
	{
		//OnPurgeProcChamber();
		EVT::ChamberNotClean.Report("Process");
		return false;
	}

	NEW_UNIT_STEP("vent", true)
		ADD_STEP_COMMAND([&]()
		{	Data::doVacFastProcCbVal = 0;
			Data::doVacSlowProcCbVal = 0;
			Data::doN2SupplyProcVal = 1;
			Data::doExpCbSupplyCbVal = 0;})
		ADD_STEP_WAIT_CONDITION([&]()->bool
		{	return Data::aiProcChamPressure > Parameters::ATMPressure;},
			Parameters::VentProcTimeout,
			[&](){	EVT::VentTimeout.Report("process");})
		ADD_STEP_COMMAND([&](){	Data::doN2SupplyProcVal = 0;})
	END_UNIT_STEP

	return true;
}

void ProcessUnit::OnPurge(unsigned param)
{
	switch(param)
	{
	case 0:
		OnPurgeProcChamber();
		break;
	case 1:
		OnPurgeExpChamber();
		break;
	case 2:
		OnPurgeHF();
		break;
	case 3:
		OnPurgeEtOH();
		break;
	default:
		;
	}
}

void ProcessUnit::OnPurgeHF()
{
	NEW_UNIT_STEP("prepare purge HF", false)
		ADD_STEP_COMMAND([&]()
		{	Data::doHFFacSupplyVal = 0;
			Data::doHFMFCVal1 = 1;
			Data::doHFMFCVal2 = 1;
			Data::doHFMFCVal3 = 1;
			Data::doExpCbHFInletVal = 0;
			Data::doVaHFValve = 1;
			Data::doExpCbVapVacValve = 0;
			Data::doVaVapValve = 0;
			Data::doExpCbVacValve = 1;})
	END_UNIT_STEP

	for(unsigned i=0; i<Parameters::PurgeRepeatTimes; i++)
	{
		NEW_UNIT_STEP("purge HF", false)
			ADD_STEP_COMMAND([&]()
			{	Data::doN2PurgeHFVal = 1;
				Data::aoHFFlowSetpoint = Parameters::HFPurgeFlow;})
			ADD_STEP_WAIT(Parameters::PurgeHoldTime)
			ADD_STEP_COMMAND([&]()
			{	Data::doN2PurgeHFVal = 0;
				Data::aoHFFlowSetpoint = 0;})
			ADD_STEP_WAIT(Parameters::PumpHoldTime)
		END_UNIT_STEP
	}

	NEW_UNIT_STEP("finish purge HF", false)
		ADD_STEP_COMMAND([&]()
		{	Data::doHFMFCVal1 = 0;
			Data::doHFMFCVal2 = 0;
			Data::doHFMFCVal3 = 0;
			Data::doVaHFValve = 0;
			Data::doExpCbVacValve = 0;})
	END_UNIT_STEP
}

void ProcessUnit::OnPurgeEtOH()
{
	if(Data::diAlcTkLow == 0)
	{
		EVT::GenericWarning.Report("Alcohol tank isn't empty, please make it empty before purge.");
		return;
	}

	NEW_UNIT_STEP("prepare purge EtOH", false)
		ADD_STEP_COMMAND([&]()
		{	Data::doExpCbVapVacValve = 0;
			Data::doExpCbVacIPASupply = 0;
			Data::doVaHFValve = 0;
			Data::doN2PurgeHFVal = 0;
			Data::doVaVapValve = 1;
			Data::doExpCbVacValve = 1;
			Data::doVapSupplyN2Valve = 0;
			Data::doVapBypassValve = 0;
			Data::doVaSupplyIPAValve = 1;
			Data::doAlcTankOpen = 1;
			Data::doPurgeAlcTank = 1;
			Data::doAlcMFCVal1 = 1;
			Data::doAlcMFCVal2 = 1;
			Data::doAlcMFCVal3 = 1;})
	END_UNIT_STEP

	for(unsigned i=0; i<Parameters::PurgeRepeatTimes; i++)
	{
		NEW_UNIT_STEP("purge EtOH", false)
			ADD_STEP_COMMAND([&]()
			{	Data::doPurgeAlcTank = 1;
				Data::aoEtOHFlowSetpoint = Parameters::EtOHPurgeFlow;})
			ADD_STEP_WAIT(Parameters::PurgeHoldTime)
			ADD_STEP_COMMAND([&]()
			{	Data::doPurgeAlcTank = 0;
				Data::aoEtOHFlowSetpoint = 0;})
			ADD_STEP_WAIT(Parameters::PumpHoldTime)
		END_UNIT_STEP
	}

	NEW_UNIT_STEP("finish purge EtOH", false)
		ADD_STEP_COMMAND([&]()
		{	Data::doAlcMFCVal1 = 0;
			Data::doAlcMFCVal2 = 0;
			Data::doAlcMFCVal3 = 0;
			Data::doVaVapValve = 0;
			Data::doExpCbVacValve = 0;
			Data::doVaSupplyIPAValve = 0;
			Data::doAlcTankOpen = 0;
			Data::doPurgeAlcTank = 0;})
	END_UNIT_STEP
}

void ProcessUnit::OnPurgeExpChamber()
{
	NEW_UNIT_STEP("prepare purge expansion chamber", false)
		ADD_STEP_COMMAND([&]()
		{	Data::doExpCbHFInletVal = 0;
			Data::doExpCbVacIPASupply = 0;
			Data::doExpCbSupplyCbVal = 0;
			Data::doVaHFValve = 0;
			Data::doVaVapValve = 0;
			Data::doExpCbVapVacValve = 1;
			Data::doExpCbVacValve = 1;
			Data::doPurgeN2MFCVal1 = 0;
			Data::doPurgeN2MFCVal2 = 1;})
	END_UNIT_STEP

	for(unsigned i=0; i<Parameters::PurgeRepeatTimes; i++)
	{
		NEW_UNIT_STEP("purge expansion chamber", false)
			ADD_STEP_COMMAND([&]()
			{	Data::doPurgeN2MFCVal1 = 1;
				Data::aoPurgeN2FlowSetpoint = Parameters::N2PurgeFlow;})
			ADD_STEP_WAIT(Parameters::PurgeHoldTime)
			ADD_STEP_COMMAND([&]()
			{	Data::doPurgeN2MFCVal1 = 0;
				Data::aoPurgeN2FlowSetpoint = 0;})
			ADD_STEP_WAIT(Parameters::PumpHoldTime)
		END_UNIT_STEP
	}

	NEW_UNIT_STEP("finish purge expansion chamber", false)
		ADD_STEP_COMMAND([&]()
		{	Data::doPurgeN2MFCVal2 = 0;
			m_exp_dirty_flag = false;})
	END_UNIT_STEP
}

void ProcessUnit::OnPurgeProcChamber()
{
	if(Data::aiProcChamPressure > Parameters::FastSlowSwitchPressure)
	{
		EVT::GenericWarning.Report("Chamber pressure is too high, please pump process chamber.");
		return;
	}

	NEW_UNIT_STEP("prepare purge process chamber", false)
		ADD_STEP_COMMAND([&]()
		{	Data::doExpCbSupplyCbVal = 0;
			Data::doN2SupplyProcVal = 0;
			Data::aoAPCPosition = 100;
			Data::aoAPCControlMode = APCControl_Position;
			Data::doVacFastProcCbVal = 1;
			Data::doVacSlowProcCbVal = 0;})
		auto condition_function = [&](){return Data::aiProcChamPressure < Parameters::PumpDownTargetPressure;};
		float pressure1 = Data::aiProcChamPressure;
		float pressure2 = Parameters::PumpDownTargetPressure;
		auto event_function = [=](){EVT::PumpTimeout.Report<float, float>(pressure1, pressure2);};
		ADD_STEP_WAIT_CONDITION(condition_function,	Parameters::FastPumpTimeout, event_function);
	END_UNIT_STEP

	for(unsigned i=0; i<Parameters::PurgeRepeatTimes; i++)
	{
		NEW_UNIT_STEP("purge process chamber", false)
			ADD_STEP_COMMAND([&]()
			{	Data::doN2SupplyProcVal = 1;})
			ADD_STEP_WAIT(Parameters::PurgeHoldTime)
			ADD_STEP_COMMAND([&]()
			{	Data::doN2SupplyProcVal = 0;})
			ADD_STEP_WAIT(Parameters::PumpHoldTime)
		END_UNIT_STEP
	}

	NEW_UNIT_STEP("finish purge process chamber", false)
		ADD_STEP_COMMAND([this]()
		{	m_proc_dirty_flag = false;})
	END_UNIT_STEP
}

void ProcessUnit::OnTurnOnHeater()
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
}

void ProcessUnit::OnTurnOffHeater()
{
	NEW_UNIT_STEP("turn on heater", false)
		ADD_STEP_COMMAND([&]()
		{	Data::doBodyHTEnable = 0;
			Data::doLidHTEnable = 0;
			Data::doChuckHTEnable = 0;})
	END_UNIT_STEP
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

	if(m_proc_dirty_flag)
	{
		EVT::GenericWarning.Report("Chamber is not clean, gate valve can't be opened.");
		return false;
	}

	NEW_UNIT_STEP("open door", true)
		ADD_STEP_COMMAND([&]()
		{	Data::doCbGateVal = 1;})
		ADD_STEP_WAIT_CONDITION([&]()->bool
		{	return Data::diPrcCbDoorOpen == 1 && Data::diPrcCbDoorClose == 0;},
			Parameters::GateValveTimeout,
			[&](){	EVT::GateValveTimeout.Report();})
	END_UNIT_STEP

	return true;
}

void ProcessUnit::OnCloseDoor()
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
			Parameters::GateValveTimeout,
			[&](){	EVT::GateValveTimeout.Report();})
	END_UNIT_STEP
}
