/*
 * ProcessChamber.h
 *
 *  Created on: 2014Äê2ÔÂ20ÈÕ
 *      Author: acm
 */

#ifndef PROCESSUNIT_H_
#define PROCESSUNIT_H_

#include "SmartUnit.h"

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

private:
	void OnHome();
	void OnLoad();
	void OnProcess();
	void OnUnload();
	void OnClean();

};

#endif /* PROCESSCHAMBER_H_ */
