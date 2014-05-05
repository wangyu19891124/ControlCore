/*
 * ProcessChamber.h
 *
 *  Created on: 2014Äê2ÔÂ20ÈÕ
 *      Author: acm
 */

#ifndef PROCESSUNIT_H_
#define PROCESSUNIT_H_

#include "SmartUnit.h"

enum AxisControl : unsigned
{
	AxisStop = 0,
	AxisReset = 1,
	AxisMoveAbsolute = 2,
	AxisMoveRelative = 3,
	AxisMoveVelocity = 4,
	AxisHoming = 5
};

enum LightControl : unsigned
{
	LightOff = 0,
	LightOn = 1,
	LightFlash = 256
};

enum APCMode : unsigned
{
	PressureMode = 1,
	PositionMode = 2
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
	virtual void SafeHandle();
	virtual void TranslateTask(const UnitTask& task);
	virtual void Notify(const std::string& msg);
	virtual void OnAbort();
	virtual bool OnlinePrecheck();

private:
	bool OnHome();
	bool OnLoad();
	bool OnProcess();
	bool OnUnload();
	bool OnClean();
	bool OnPinUp();
	bool OnPinDown();
	bool OnRotateForward();
	bool OnRotateBackward();
	bool OnPump();
	bool OnVent();
	bool OnPurge();
	bool OnTurnOnHeater();
	bool OnTurnOffHeater();
	bool OnOpenDoor();
	bool OnCloseDoor();

private:
	float get_next_position();
	float get_last_position();
	void create_wafer(int unit, unsigned short slot);
	void remove_wafer(int unit, unsigned short slot);

private:
	bool m_dirty_flag;
	int m_load_unload_count;

};

#endif /* PROCESSCHAMBER_H_ */
