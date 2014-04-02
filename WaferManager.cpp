/*
 * WaferManager.cpp
 *
 *  Created on: 2014Äê2ÔÂ24ÈÕ
 *      Author: acm
 */

#include <iomanip>
#include <sstream>

#include "boost/date_time.hpp"

#include "WaferManager.h"

void WaferManager::Initialize()
{

}

void WaferManager::Terminate()
{

}

void WaferManager::CreateWafer(int unit, const std::string& casset_id, WaferSize size, WaferType type, unsigned int mapping)
{
	mapping = mapping & DEFAULT_FOUP_MAPPING;

	boost::mutex::scoped_lock lock(m_mtx);
	for(unsigned short i=0; i<MAX_SLOT_NUM; i++)
	{
		int index = unit*100 + i;
		bool flag = mapping & 0x1;
		if(flag)
		{
			m_wafers[index] = boost::shared_ptr<Wafer>(new Wafer(generate_wafer_id(casset_id), unit, i, size, type));
		}
		mapping = mapping>>1;
		if(mapping == 0)
			return;
	}
}

void WaferManager::RemoveWafer(int unit, unsigned int mapping)
{
	mapping = mapping & DEFAULT_FOUP_MAPPING;

	boost::mutex::scoped_lock lock(m_mtx);
	for(int i=0; i<MAX_SLOT_NUM; i++)
	{
		int index = unit*100 + i;
		bool flag = mapping & 0x1;
		if(flag)
		{
			m_wafers[index].reset();
		}
		mapping = mapping>>1;
		if(mapping == 0)
			return;
	}
}

void WaferManager::Transfer(int src_unit, unsigned short src_slot, int dest_unit, unsigned short dest_slot)
{
	int dest_index = dest_unit*100 + dest_slot;
	int src_index = src_unit*100 + src_slot;

	boost::mutex::scoped_lock lock(m_mtx);
	m_wafers[dest_index] = m_wafers[src_index];
	m_wafers[src_index].reset();
}

bool WaferManager::HasWafer(int unit, unsigned short slot)
{
	boost::mutex::scoped_lock lock(m_mtx);
	int index = unit*100 + slot;
	boost::shared_ptr<Wafer> wf = m_wafers[index];

	return wf ? true : false;
}

WaferSite WaferManager::GetOriginalSite(int unit, unsigned short slot)
{
	boost::mutex::scoped_lock lock(m_mtx);
	int index = unit*100 + slot;

	return m_wafers[index]->GetOriginalSite();
}

WaferType WaferManager::GetType(int unit, unsigned short slot)
{
	boost::mutex::scoped_lock lock(m_mtx);
	int index = unit*100 + slot;

	return m_wafers[index]->GetType();
}

WaferSize WaferManager::GetSize(int unit, unsigned short slot)
{
	boost::mutex::scoped_lock lock(m_mtx);
	int index = unit*100 + slot;

	return m_wafers[index]->GetSize();
}

void WaferManager::ProcessStart(int unit, const std::string& recipe)
{
	boost::mutex::scoped_lock lock(m_mtx);
	int index = unit*100;

	m_wafers[index]->ProcessStart(recipe);
}

void WaferManager::ProcessEnd(int unit)
{
	boost::mutex::scoped_lock lock(m_mtx);
	int index = unit*100;

	m_wafers[index]->ProcessEnd();
}

void WaferManager::ProcessAbort(int unit)
{
	boost::mutex::scoped_lock lock(m_mtx);
	int index = unit*100;

	m_wafers[index]->ProcessAbort();
}

void WaferManager::WaferBroken(int unit, unsigned short slot)
{
	boost::mutex::scoped_lock lock(m_mtx);
	int index = unit*100 + slot;

	boost::shared_ptr<Wafer> wf = m_wafers[index];
	wf->Broken();
	WaferSite site = wf->GetOriginalSite();
	int orig_index = site.first*100 + site.second;
	m_wafers[orig_index] = wf;
	m_wafers[index].reset();
}

void WaferManager::SetRoute(int unit, unsigned short slot, const std::list<WaferSite>& route)
{
	boost::mutex::scoped_lock lock(m_mtx);
	int index = unit*100 + slot;

	m_wafers[index]->SetRoute(route);
}

bool WaferManager::HasRoute(int unit, unsigned short slot)
{
	boost::mutex::scoped_lock lock(m_mtx);
	int index = unit*100 + slot;

	return m_wafers[index]->HasRoute();
}

WaferSite WaferManager::GetNextSite(int unit, unsigned short slot)
{
	boost::mutex::scoped_lock lock(m_mtx);
	int index = unit*100 + slot;

	return m_wafers[index]->GetNextSite();
}

bool WaferManager::IsWaferAllProcessed(int unit, unsigned int mapping)
{
	mapping = mapping & DEFAULT_FOUP_MAPPING;

	boost::mutex::scoped_lock lock(m_mtx);
	boost::shared_ptr<Wafer> wf;
	for(int i=0; i<MAX_SLOT_NUM; i++)
	{
		bool flag = mapping & 0x1;
		if(flag)
		{
			int index = unit*100 + i;
			wf = m_wafers[index];
			if(!wf || !wf->IsProcessed())
				return false;
		}
		mapping = mapping>>1;
		if(mapping == 0)
			break;
	}

	return true;
}

bool WaferManager::HasWaferUnprocessed(int unit, unsigned int mapping)
{
	mapping = mapping & DEFAULT_FOUP_MAPPING;

	boost::mutex::scoped_lock lock(m_mtx);
	boost::shared_ptr<Wafer> wf;
	for(int i=0; i<MAX_SLOT_NUM; i++)
	{
		bool flag = mapping & 0x1;
		if(flag)
		{
			int index = unit*100 + i;
			wf = m_wafers[index];
			if(wf && wf->IsUnprocessed())
				return true;
		}
		mapping = mapping>>1;
		if(mapping == 0)
			break;
	}

	return false;
}

unsigned short WaferManager::GetUnprocessedWaferSlot(int unit, unsigned int mapping)
{
	mapping = mapping & DEFAULT_FOUP_MAPPING;

	boost::mutex::scoped_lock lock(m_mtx);
	boost::shared_ptr<Wafer> wf;
	for(unsigned short i=0; i<MAX_SLOT_NUM; i++)
	{
		bool flag = mapping & 0x1;
		if(flag)
		{
			int index = unit*100 + i;
			wf = m_wafers[index];
			if(wf && wf->IsUnprocessed())
				return i;
		}
		mapping = mapping>>1;
		if(mapping == 0)
			break;
	}

	return MAX_SLOT_NUM;
}

std::string WaferManager::generate_wafer_id(const std::string& casset_id)
{
	using namespace boost::posix_time;
	ptime t = second_clock::local_time();
	std::stringstream ss;
	ss<<to_iso_string(t).substr(2, 6)<<std::setw(4)<<std::setfill('0')<<((m_count++)%10000);

	return ss.str();
}
