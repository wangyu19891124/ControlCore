/*
 * SystemData.cpp
 *
 *  Created on: 2014Äê2ÔÂ25ÈÕ
 *      Author: acm
 */

#include "boost/algorithm/string.hpp"

#include "SystemData.h"

BaseSystemData::BaseSystemData(int id, const std::string& name,
		const std::string& path)
: m_id(id), m_name(name), m_path(path), m_changed_flag(false)
{
}

BaseSystemData::~BaseSystemData()
{
}


bool BaseSystemData::IsChild(const std::string& path)
{
	return boost::algorithm::equals(m_path, path);
}

bool BaseSystemData::HasChanged()
{
	return m_changed_flag;
}
