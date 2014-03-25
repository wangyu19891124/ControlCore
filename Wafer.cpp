/*
 * Wafer.cpp
 *
 *  Created on: 2014Äê2ÔÂ21ÈÕ
 *      Author: acm
 */

#include <iomanip>

#include "Wafer.h"

Wafer::Wafer(const std::string& casset_id, int unit, unsigned short slot,
		WaferSize size, WaferType type) :
		m_casset_id(casset_id), m_original_unit(unit), m_original_slot(slot),
		m_size(size), m_type(type)
{
	// TODO Auto-generated constructor stub

}

Wafer::~Wafer()
{
	// TODO Auto-generated destructor stub
}

WaferSite Wafer::GetOriginalSite()
{
	return std::make_pair(m_original_unit, m_original_slot);
}
//
//WaferSite Wafer::GetSite()
//{
//	return std::make_pair(m_unit, m_slot);
//}

WaferType Wafer::GetType()
{
	return m_type;
}

WaferSize Wafer::GetSize()
{
	return m_size;
}

std::string Wafer::GetID()
{
	std::stringstream ss;
	ss<<m_casset_id<<"-"<<std::setw(2)<<std::setfill('0')<<m_original_slot;
	return ss.str();
}

void Wafer::Transfer(int dest_unit, unsigned short dest_slot)
{
//	m_unit = dest_unit;
//	m_slot = dest_slot;
	if(!m_route.empty() && m_route.begin()->first == dest_unit)
		m_route.pop_front();
}

void Wafer::ProcessStart(const std::string& recipe)
{
	m_recipe = recipe;
	m_process_start_time = boost::chrono::system_clock::now();
	if(m_type == Wafer_Unprocessed)
		m_type = Wafer_Processing;
}

void Wafer::ProcessEnd()
{
	m_process_end_time = boost::chrono::system_clock::now();
	if(m_type == Wafer_Processing)
		m_type = Wafer_Processed;
}

void Wafer::ProcessAbort()
{
	m_process_end_time = boost::chrono::system_clock::now();
	if(m_type == Wafer_Processing)
		m_type = Wafer_Semi_Processed;
}

void Wafer::Broken()
{
//	m_unit = m_original_unit;
//	m_slot = m_original_slot;
	m_type = Wafer_Broken;
}

void Wafer::SetRoute(const std::list<WaferSite>& route)
{
	m_route = route;
}

bool Wafer::HasRoute()
{
	return !m_route.empty();
}

WaferSite Wafer::GetNextSite()
{
	if(!m_route.empty())
		return *(m_route.begin());

	return std::make_pair<int, unsigned short>(-1, 0);
}

bool Wafer::IsProcessed()
{
	switch(m_type)
	{
	case Wafer_Processed:
	case Wafer_Semi_Processed:
	case Wafer_Broken:
		return true;
		break;
	default:
		return false;
	}

	return false;
}

bool Wafer::IsUnprocessed()
{
	return m_type == Wafer_Unprocessed;
}

bool Wafer::IsDummy()
{
	return m_type == Wafer_Dummy;
}


