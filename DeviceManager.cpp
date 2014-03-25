/*
 * DeviceManager.cpp
 *
 *  Created on: 2014Äê3ÔÂ3ÈÕ
 *      Author: acm
 */

#include "boost/algorithm/string.hpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/xml_parser.hpp"

#include "DeviceManager.h"

void DeviceManager::Initialize()
{
	using namespace boost::property_tree;
	ptree pt;
	xml_parser::read_xml("./Device.xml", pt);
	for(ptree::value_type &v : pt.get_child("DeviceList"))
	{
		int id = v.second.get<int>("<xmlattr>.id");
		std::string name = v.second.get<std::string>("<xmlattr>.name");
		CreateDevice(id, name);
	}
}

void DeviceManager::Terminate()
{
	for(std::map<int, Device*>::value_type &v : m_devices)
	{
		v.second->Terminate();
		delete v.second;
		v.second = nullptr;
	}
	m_devices.clear();
}

Device& DeviceManager::GetDevice(int id)
{
	auto itor = m_devices.find(id);
	if(itor != m_devices.end())
		return *(itor->second);
	else
	{
		std::stringstream ss;
		ss<<"Device "<<id<<" doesn't exist.";
		throw ss.str();
	}
}

void DeviceManager::CreateDevice(int id, const std::string& dev_name)
{
	//assert(id >= 0);
	if(boost::algorithm::iequals("simulator", dev_name))
	{
		//create simulator device and add to container
	}
	//else if()
	//else
}
