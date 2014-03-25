/*
 * ProcessChamber.h
 *
 *  Created on: 2014Äê2ÔÂ20ÈÕ
 *      Author: acm
 */

#ifndef PROCESSCHAMBER_H_
#define PROCESSCHAMBER_H_

#include "SmartUnit.h"

class ProcessChamber: public SmartUnit,
		public boost::noncopyable
{
public:
	ProcessChamber(int id);
	virtual ~ProcessChamber();

	virtual void Initialize();
	virtual void Terminate();

protected:
	virtual UnitTask GetNextTask();
	virtual void UpdateUnitInfo();
	virtual void SafeHandle();
	virtual bool TranslateTask(const UnitTask& task);

private:
	void OnHome();
	void OnLoad();
	void OnProcess();
	void OnUnload();
	void OnClean();

};

#endif /* PROCESSCHAMBER_H_ */
