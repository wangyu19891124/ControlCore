/*
 * DataRecorder.cpp
 *
 *  Created on: 2014Äê3ÔÂ20ÈÕ
 *      Author: acm
 */

#include "boost/make_shared.hpp"
#include "boost/date_time/posix_time/ptime.hpp"

#include "DataRecorder.h"


RecordItem::RecordItem(RecordItemID id, const std::string& name, unsigned interval, boost::function<float ()> f, bool enable)
	: m_id(id), m_name(name), m_interval(interval), m_f(f), m_enable_flag(enable)
{
	m_last_record_time = boost::chrono::system_clock::now();
}
//
//RecordItem::RecordItem(const RecordItem& other)
//	: RecordItem(other.m_id, other.m_name, other.m_interval, other.m_f, other.m_enable_flag)
//{
//
//}

//RecordItem& RecordItem::operator = (const RecordItem& rhs)
//{
//	m_id = rhs.m_id;
//	m_name = rhs.m_name;
//	m_interval = rhs.m_interval;
//	m_f = rhs.m_f;
//	m_enable_flag = rhs.m_enable_flag;
//	m_last_record_time = rhs.m_last_record_time;
//
//	return *this;
//}

bool RecordItem::operator == (const RecordItem& rhs)
{
	return m_id == rhs.m_id;
}

RecordItemID RecordItem::GetID()
{
	return m_id;
}

void RecordItem::Enable()
{
	m_enable_flag = true;
}

void RecordItem::Disable()
{
	m_enable_flag = false;
}

void RecordItem::Monitor()
{
	if(!m_enable_flag)
		return;

	using namespace boost::chrono;
	auto dur = system_clock::now() - m_last_record_time;
	if(dur > milliseconds(m_interval))
	{
		//record data to database
		float data = m_f();
		auto record_time = system_clock::now();
		//TODO

		m_last_record_time = record_time;
	}
}


void DataRecorder::Initialize()
{
	if(!m_items.empty())
		return;

	//Add Recorder Item
	//TODO
	//m_items.push_back(boost::make_shared<RecordItem>(RecordItem_N2, "N2", 1000, [](){return 0.0f;}));

	//start record thread
	if(m_thrd)
		m_thrd.reset(new boost::thread(boost::bind(&DataRecorder::monitor, this)));

}

void DataRecorder::Terminate()
{
	if(!m_thrd)
		return;

	m_thrd->interrupt();
	m_thrd->join();

	m_items.clear();
}

void DataRecorder::Enable(RecordItemID id)
{
	boost::mutex::scoped_lock lock(m_mtx);
	for(auto& item : m_items)
	{
		if(item->GetID() == id)
		{
			item->Enable();
			break;
		}
	}
}

void DataRecorder::Disable(RecordItemID id)
{
	boost::mutex::scoped_lock lock(m_mtx);
	for(auto& item : m_items)
	{
		if(item->GetID() == id)
		{
			item->Disable();
			break;
		}
	}
}

void DataRecorder::Add(boost::shared_ptr<RecordItem> item)
{
	boost::mutex::scoped_lock lock(m_mtx);
	for(auto& x : m_items)
	{
		if(*item == *x)
		{
			break;
		}
	}

	m_items.push_back(item);
}

void DataRecorder::Remove(RecordItemID id)
{
	boost::mutex::scoped_lock lock(m_mtx);
	m_items.remove_if([id](boost::shared_ptr<RecordItem>& x){return x->GetID() == id;});
}

void DataRecorder::monitor()
{
	boost::this_thread::disable_interruption di;

	using namespace boost::posix_time;
	auto t = microsec_clock::universal_time();

	while(true)
	{
		t += milliseconds(50);
		{
			boost::mutex::scoped_lock lock(m_mtx);
			for(auto& x : m_items)
			{
				x->Monitor();
			}
		}

		if (boost::this_thread::interruption_requested())
			break;

		boost::this_thread::sleep(t);
	}
}
