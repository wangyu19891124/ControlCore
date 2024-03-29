/*
 * Monitor.cpp
 *
 *  Created on: 2014��5��14��
 *      Author: Administrator
 */

#include "Monitor.h"

void Monitor::Initialize()
{
	//initialize monitor items

	//startup thread
	if(!m_thrd_ptr)
		m_thrd_ptr.reset(new boost::thread([this](){do_work();}));
}

void Monitor::Terminate()
{
	if(m_thrd_ptr)
	{
		m_thrd_ptr->interrupt();
		m_thrd_ptr->join();
		m_thrd_ptr.reset(nullptr);
	}

	m_items.clear();
}

void Monitor::EnableAll()
{
	boost::mutex::scoped_lock lock(m_mtx);
	for(auto& x : m_items)
	{
		x.second->Enable();
	}
}

void Monitor::DisableAll()
{
	boost::mutex::scoped_lock lock(m_mtx);
	for(auto& x : m_items)
	{
		x.second->Disable();
	}
}

void Monitor::Enable(const std::string& name)
{
	boost::mutex::scoped_lock lock(m_mtx);
	boost::shared_ptr<MonitorItem> item_ptr = m_items[name];
	if(item_ptr)
	{
		item_ptr->Enable();
	}
}

void Monitor::Disable(const std::string& name)
{
	boost::mutex::scoped_lock lock(m_mtx);
	boost::shared_ptr<MonitorItem> item_ptr = m_items[name];
	if(item_ptr)
	{
		item_ptr->Disable();
	}
}

void Monitor::Reset(const std::string& name, float setpoint, float warn_offset, float alarm_offset)
{
	boost::mutex::scoped_lock lock(m_mtx);
	boost::shared_ptr<MonitorItem> item_ptr = m_items[name];
	if(item_ptr)
	{
		item_ptr->Reset(setpoint, warn_offset, alarm_offset);
	}
}

void Monitor::Reset(const std::string& name, float setpoint)
{
	boost::mutex::scoped_lock lock(m_mtx);
	boost::shared_ptr<MonitorItem> item_ptr = m_items[name];
	if(item_ptr)
	{
		item_ptr->Reset(setpoint);
	}
}

bool Monitor::HasWarning()
{
	boost::mutex::scoped_lock lock(m_mtx);
	for(auto& x : m_items)
	{
		if(x.second->HasWarning())
			return true;
	}

	return false;
}

bool Monitor::HasAlarm()
{
	boost::mutex::scoped_lock lock(m_mtx);
	for(auto& x : m_items)
	{
		if(x.second->HasAlarm())
			return true;
	}

	return false;
}

void Monitor::do_work()
{
	boost::this_thread::disable_interruption di;

	while(true)
	{
		{
			boost::mutex::scoped_lock lock(m_mtx);
			for(auto& x : m_items)
			{
				x.second->Monitor();
			}
		}

		if (boost::this_thread::interruption_requested())
			break;

		boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
	}
}
