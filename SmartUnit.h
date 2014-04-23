/*
 * SmartUnit.h
 *
 *  Created on: 2014��2��14��
 *      Author: acm
 */

#ifndef SMARTUNIT_H_
#define SMARTUNIT_H_

#include "boost/scoped_ptr.hpp"
#include "boost/thread.hpp"

#include "TaskStep.h"

enum UnitState
{
	State_Idle = 0,
	State_Running,
	State_Error,
};

#define	TASK_NONE 0
#define	TASK_HOME 1
#define	TASK_LOAD 2
#define	TASK_UNLOAD 3
#define	TASK_PROCESS 4
#define	TASK_CLEAN 5
#define	TASK_ALIGN 6
#define TASK_PUMP 7
#define TASK_VENT 8
#define TASK_PURGE 9


struct UnitTask
{
//	UnitTask(){UnitTask(Task_None, 0, 0);}
//	UnitTask(TaskType t):type(t), para1(0), para2(0){}
//	UnitTask(TaskType t, int p1, int p2):type(t), para1(p1), para2(p2){}
	int type;
	unsigned para1;
	unsigned para2;
};


class SmartUnit
{
public:
	SmartUnit(int id, const std::string& name);
	virtual ~SmartUnit();

public:
	virtual void Initialize();
	virtual void Terminate();
	void Online(int hp = __INT_MAX__);
	void Offline();
	void Retry();
	void Abort();
	void Pause();
	void Resume();
//	virtual void Home();
	void Invoke(int cmd, unsigned param1, unsigned param2);

protected:
	virtual UnitTask GetNextTask() = 0;
	virtual void UpdateUnitInfo() = 0;
	virtual void SafeHandle() = 0;
	virtual bool TranslateTask(const UnitTask& task);

private:
	void work_fun();
	bool CanPause();
	bool CanManualOperate();

protected:
	int m_id;
	std::string m_name;
	unsigned m_hp;
	bool m_need_home;
	UnitState m_state;
	bool m_pause_flag;
	std::string m_step_name;
	bool m_can_retry;
	UnitTask m_task;
	UnitTask m_last_task;
	boost::scoped_ptr<boost::thread> m_thrd;
	boost::mutex m_mtx;
	std::list<boost::shared_ptr<TaskStep> > m_steps;
	boost::shared_ptr<TaskStep> m_cur_step;

};


#define NEW_UNIT_STEP(name, retry) { \
	boost::shared_ptr<TaskStep> step(new TaskStep(#name, retry)); \
	boost::mutex::scoped_lock lock(m_mtx);

#define ADD_STEP_COMMAND(func) step->Add(Command(func));
#define ADD_STEP_WAIT_CONDITION(cond, timeout, evt) step->Add(WaitCondition(cond, timeout, evt));
#define ADD_STEP_WAIT(timeout) step->Add(Wait(timeout));
#define ADD_STEP_EXPECT(cond, duration, evt) step->Add(Expect(cond, duration, evt));

#define END_UNIT_STEP m_steps.push_back(step); \
	}


#endif /* SMARTUNIT_H_ */
