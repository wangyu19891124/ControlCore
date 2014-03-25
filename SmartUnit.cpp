/*
 * SmartUnit.cpp
 *
 *  Created on: 2014Äê2ÔÂ19ÈÕ
 *      Author: acm
 */
#include "SmartUnit.h"

SmartUnit::SmartUnit(int id) :
		m_id(id), m_hp(0), m_need_home(true), m_state(State_Idle),
		m_pause_flag(false), m_step_name(""), m_can_retry(false)
{
	m_last_task = UnitTask{Task_None, 0, 0};
	m_task = UnitTask{Task_None, 0, 0};
}

SmartUnit::~SmartUnit()
{
}

void SmartUnit::Initialize()
{
	//subclass should call __base::Initialize in the last
	boost::function<void ()> f;
	f = boost::bind(&SmartUnit::work_fun, this);
	m_thrd.reset(new boost::thread(f));
}
void SmartUnit::Terminate()
{
	//subclass should call __base::Terminate in the first
	m_thrd->interrupt();
	m_thrd->join();
}

void SmartUnit::Online(int hp)
{
	boost::mutex::scoped_lock lock(m_mtx);
	m_hp = hp;
}
void SmartUnit::Offline()
{
	boost::mutex::scoped_lock lock(m_mtx);
	m_hp = 0;
}

void SmartUnit::Retry()
{
	if (m_state == State_Error && m_can_retry)
	{
		boost::mutex::scoped_lock lock(m_mtx);
		m_cur_step->Reset();
		m_state = State_Running;
	}
}

void SmartUnit::Abort()
{
	if (m_state != State_Error)
		return;

	boost::mutex::scoped_lock lock(m_mtx);
	m_cur_step.reset();
	m_steps.clear();
	m_step_name = "";
	m_can_retry = false;
	m_hp = 0;
	m_need_home = true;
	m_state = State_Idle;
}

//void SmartUnit::Home()
//{
//	//subclass should call __base::Home at end
//	m_need_home = false;
//}

void SmartUnit::Pause()
{
	if (m_state == State_Error)
		return;

	if (CanPause())
		m_pause_flag = true;
}

void SmartUnit::Resume()
{
	m_pause_flag = false;
}

bool SmartUnit::TranslateTask(const UnitTask& task)
{
	if (m_task.type != Task_None && task.type != m_task.type)
		m_last_task = m_task;

	m_task = task;

	if (task.type == Task_None)
		return false;

	{
		boost::mutex::scoped_lock lock(m_mtx);
		m_hp--;
	}

	return true;
	//subclass implement in the following
}

void SmartUnit::work_fun()
{
	boost::this_thread::disable_interruption di;
	unsigned int loop_interval = 50; //ms, this value can read from config in the future

	while (true)
	{
		if (m_state == State_Idle)
		{
			if (!m_pause_flag)
			{
				if (m_steps.size() > 0)
				{
					m_state = State_Running;
					continue;
				}
				else
				{
					if (m_hp > 0)
					{
						UnitTask task = GetNextTask();
						TranslateTask(task);
					}
				}
			}
		}
		else if (m_state == State_Running)
		{
			if (!m_cur_step && m_steps.empty())
			{
				m_state = State_Idle;
				continue;
			}

			if (!m_pause_flag && !m_cur_step)
			{
				boost::mutex::scoped_lock lock(m_mtx);
				m_cur_step = *(m_steps.begin());
				m_steps.pop_front();
				m_step_name = m_cur_step->GetName();
				m_can_retry = m_cur_step->CanRetry();
			}

			if (m_cur_step)
			{
				int rtv = m_cur_step->Execute();
				std::cout<<"execute result: "<<rtv<<std::endl;
				if (rtv == RESULT_OK)
				{
					m_step_name = "";
					m_can_retry = false;
					m_cur_step.reset();
				}
				else if (rtv == RESULT_FAILED)
				{
					SafeHandle();
					m_state = State_Error;
				}
			}
		}
		else
		{
			//error state, do nothing
		}

		//update unit information
		UpdateUnitInfo();

		if (boost::this_thread::interruption_requested())
			break;

		boost::this_thread::sleep_for(
				boost::chrono::milliseconds(loop_interval));
	}

	std::cout<<"smart unit thread exit!"<<std::endl;
}

bool SmartUnit::CanPause()
{
	switch (m_task.type)
	{
	case Task_Process:
	case Task_Clean:
	case Task_Load:
	case Task_Unload:
		return false;
	default:
		return true;
	}

	return true;
}

bool SmartUnit::CanManualOperate()
{
	if(m_hp > 0 || m_state != State_Idle)
		return false;

	boost::mutex::scoped_lock lock(m_mtx);
	if(!m_steps.empty())
		return false;

	return true;
}
