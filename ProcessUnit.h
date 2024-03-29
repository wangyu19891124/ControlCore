/*
 * ProcessChamber.h
 *
 *  Created on: 2014��2��20��
 *      Author: acm
 */

#ifndef PROCESSUNIT_H_
#define PROCESSUNIT_H_

#include "SmartUnit.h"


enum AxisControl : unsigned
{
	AxisControl_Stop = 0,
	AxisControl_Reset = 1,
	AxisControl_Absolute = 2,
	AxisControl_Relative = 3,
	AxisControl_Velocity = 4,
	AxisControl_Homing = 5,
};

enum LightControl : unsigned
{
	LightControl_Off = 0,
	LightControl_On = 1,
	LightControl_Flash = 256
};

enum APCControl : unsigned
{
	APCControl_Pressure = 1,
	APCControl_Position = 2
};

class ProcessUnit: public SmartUnit,
		public boost::noncopyable
{
public:
	ProcessUnit(int id, const std::string& name);
	virtual ~ProcessUnit();

	virtual void Initialize();
	virtual void Terminate();

protected:
	virtual UnitTask GetNextTask();
	virtual void UpdateUnitInfo();
	virtual void ErrorHandle();
	virtual void TranslateTask(const UnitTask& task);
	virtual void Notify(const std::string& msg);
	virtual void OnAbort();
	virtual bool OnlinePrecheck();

private:
	void OnHome();
	void OnLoad();
	void OnUnload();
	void OnProcess();

	void OnLeakCheck(unsigned param);
	void OnExpChamberLeakCheck();
	void OnProcChamberLeakCheck();

	void OnPinUp();
	void OnPinDown();

	void OnRotateForward();
	void OnRotateBackward();

	void OnPump(unsigned param);
	bool OnPumpExpChamber();
	bool OnPumpProcChamber();

	void OnVent(unsigned param);
	bool OnVentExpChamber();
	bool OnVentProcChamber();

	void OnPurge(unsigned param);
	void OnPurgeHF();
	void OnPurgeEtOH();
	void OnPurgeExpChamber();
	void OnPurgeProcChamber();

	void OnTurnOnHeater();
	void OnTurnOffHeater();

	bool OnOpenDoor();
	void OnCloseDoor();

private:
	float get_next_position();
	float get_last_position();
	void create_wafer(int unit, unsigned short slot);
	void remove_wafer(int unit, unsigned short slot);
	void process_recipe_step(unsigned int index, const RecipeStep& recipe_step);

private:
	bool m_proc_dirty_flag;
	bool m_exp_dirty_flag;
	int m_load_unload_count;

	float m_leak_check_init_pressure;

	boost::chrono::time_point<boost::chrono::system_clock> m_recipe_start_time;
	boost::chrono::time_point<boost::chrono::system_clock> m_step_start_time;

};

#endif /* PROCESSCHAMBER_H_ */
