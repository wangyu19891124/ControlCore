/*
 * SystemDataPool.cpp
 *
 *  Created on: 2014Äê3ÔÂ5ÈÕ
 *      Author: acm
 */

#include "SystemDataPool.h"
#include "Data.h"

void SystemDataPool::Initialize()
{
	InitializeData(Data::flag);
}

void SystemDataPool::Terminate()
{
	TerminateData(Data::flag);

	m_all_data.clear();
}

std::string SystemDataPool::ToJson(boost::function<bool (BaseSystemData*)> f)
{
	using namespace boost::property_tree;
	ptree array;
	BaseSystemData* data_ptr = nullptr;
	for(std::map<int, BaseSystemData*>::value_type& v : m_all_data)
	{
		data_ptr = v.second;
		if(data_ptr && (!f || f(data_ptr)))
			data_ptr->Serialize(array);
	}
	ptree pt;
	pt.add_child("systemdata", array);

	std::stringstream ss;
	json_parser::write_json(ss, pt);

	return ss.str();
}
