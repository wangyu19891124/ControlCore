/*
 * Wafer.cpp
 *
 *  Created on: 2014��2��21��
 *      Author: acm
 */

#include <iomanip>

#include "Database.h"
#include "Wafer.h"

Wafer::Wafer(const std::string& id, int unit, unsigned short slot,
		WaferSize size, WaferType type, WaferState state) :
		m_id(id), m_original_unit(unit), m_original_slot(slot),
		m_size(size), m_type(type), m_state(state)
{
	Database::Instance().CreateWafer(m_id, wafer_type_to_string(type), wafer_size_to_string(size));
	Database::Instance().WaferEnter(m_id, unit, slot, wafer_state_to_string(m_state));
}

Wafer::~Wafer()
{
	Database::Instance().WaferExit(m_id, wafer_state_to_string(m_state));
	Database::Instance().RemoveWafer(m_id);
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

WaferState Wafer::GetState()
{
	return m_state;
}

std::string Wafer::GetID()
{
	return m_id;
}

void Wafer::Transfer(int dest_unit, unsigned short dest_slot)
{
	Database::Instance().WaferExit(m_id, wafer_state_to_string(m_state));
	Database::Instance().WaferEnter(m_id, dest_unit, dest_slot, wafer_state_to_string(m_state));
	m_unit = dest_unit;
	m_slot = dest_slot;
	if(!m_route.empty() && m_route.begin()->first == dest_unit)
		m_route.pop_front();
}

void Wafer::ProcessStart(const std::string& recipe)
{
	m_recipe = recipe;
	m_process_start_time = boost::chrono::system_clock::now();
	if(m_state == WaferState_Unprocessed)
		m_state = WaferState_Processing;
	Database::Instance().ProcessStart(m_id, m_unit, recipe);
}

void Wafer::ProcessEnd()
{
	m_process_end_time = boost::chrono::system_clock::now();
	if(m_state == WaferState_Processing)
		m_state = WaferState_Processed;
	Database::Instance().ProcessEnd(m_id);
}

void Wafer::ProcessAbort()
{
	m_process_end_time = boost::chrono::system_clock::now();
	if(m_state == WaferState_Processing)
		m_state = WaferState_Semi_Processed;
	Database::Instance().ProcessEnd(m_id);
}

void Wafer::Broken()
{
//	m_unit = m_original_unit;
//	m_slot = m_original_slot;
	m_state = WaferState_Broken;
	Database::Instance().WaferExit(m_id, wafer_state_to_string(m_state));
	Database::Instance().WaferEnter(m_id, m_original_unit, m_original_slot, wafer_state_to_string(m_state));
	m_route.clear();
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
	switch(m_state)
	{
	case WaferState_Processed:
	case WaferState_Semi_Processed:
	case WaferState_Broken:
		return true;
		break;
	default:
		return false;
	}

	return false;
}

bool Wafer::IsUnprocessed()
{
	return m_state == WaferState_Unprocessed;
}

bool Wafer::IsDummy()
{
	return m_type == WaferType_Dummy;
}

std::string Wafer::wafer_type_to_string(WaferType type)
{
	if(type == 	WaferType_Product)
		return "product";

	return "dummy";
}

std::string Wafer::wafer_size_to_string(WaferSize size)
{
	if(size == WaferSize_100mm)
		return "100mm";
	else if(size == WaferSize_150mm)
		return "150mm";
	else if(size == WaferSize_200mm)
		return "200mm";

	return "300mm";
}

std::string Wafer::wafer_state_to_string(WaferState state)
{
	if(state == WaferState_Unprocessed)
		return "unprocessed";
	else if(state == WaferState_Semi_Processed)
		return "semi_processed";
	else if(state == WaferState_Processing)
		return "processing";
	else if(state == WaferState_Processed)
		return "processed";

	return "broken";
}

