/*
 * Recipe.cpp
 *
 *  Created on: 2014Äê3ÔÂ19ÈÕ
 *      Author: acm
 */

#include "boost/algorithm/string.hpp"
#include "boost/function.hpp"

#include "Recipe.h"
#include "Utility.h"

using namespace boost::property_tree;

BypassMode RecipeStep::bypass_from_string(const std::string& mode)
{
	if(boost::algorithm::equals(mode, "chamber"))
	{
		return BypassMode_Chamber;
	}
	else if(boost::algorithm::equals(mode, "bypass"))
	{
		return BypassMode_Bypass;
	}
	else
	{
		return BypassMode_None;
	}
}

std::string RecipeStep::bypass_to_string(BypassMode mode)
{
	if(mode == BypassMode_Chamber)
	{
		return "chamber";
	}
	else if(mode == BypassMode_Bypass)
	{
		return "bypass";
	}
	else
	{
		return "none";
	}
}

APCMode RecipeStep::apc_from_string(const std::string& mode)
{
	if(boost::algorithm::equals(mode, "pressure"))
	{
		return APCMode_Pressure;
	}
	else
	{
		return APCMode_Position;
	}
}

std::string RecipeStep::apc_to_string(APCMode mode)
{
	if(mode == APCMode_Pressure)
	{
		return "pressure";
	}
	else
	{
		return "position";
	}
}

RecipeStep& RecipeStep::operator = (const RecipeStep& rhs)
{
	m_name = rhs.m_name;
	m_duration = rhs.m_duration;
	m_apc_mode = rhs.m_apc_mode;
	m_position = rhs.m_position;
	m_pressure = rhs.m_pressure;
	m_rotate_speed = rhs.m_rotate_speed;
	m_HF_bypass = rhs.m_HF_bypass;
	m_HF_flowrate = rhs.m_HF_flowrate;
	m_EtOH_bypass = rhs.m_EtOH_bypass;
	m_EtOH_flowrate = rhs.m_EtOH_flowrate;
	m_N2_flowrate = rhs.m_N2_flowrate;
	m_N2_purge_flowrate = rhs.m_N2_purge_flowrate;

	return *this;
}

void RecipeStep::Load(const boost::property_tree::ptree& pt)
{
	m_name = pt.get<std::string>("Name");
	m_duration = pt.get<unsigned short>("Time");
	std::string tmp = pt.get<std::string>("APC Mode");
	m_apc_mode = apc_from_string(tmp);
	m_position = pt.get<unsigned short>("Position");
	m_pressure = pt.get<unsigned short>("Pressure");
	m_rotate_speed = pt.get<unsigned short>("Rotate Speed");
	tmp = pt.get<std::string>("HF Bypass");
	m_HF_bypass = bypass_from_string(tmp);
	m_HF_flowrate = pt.get<unsigned short>("HF");
	tmp = pt.get<std::string>("EtOH Bypass");
	m_EtOH_bypass = bypass_from_string(tmp);
	m_EtOH_flowrate = pt.get<int>("EtOH");
	m_N2_flowrate = pt.get<int>("N2");
	m_N2_purge_flowrate = pt.get<int>("N2 Purge");
}

void RecipeStep::Save(boost::property_tree::ptree& pt)
{
	pt.put("Name", m_name);
	pt.put("Time", m_duration);
	std::string tmp = apc_to_string(m_apc_mode);
	pt.put("APC Mode", tmp);
	pt.put("Position", m_position);
	pt.put("Pressure", m_pressure);
	pt.put("Rotate Speed", m_rotate_speed);
	tmp = bypass_to_string(m_HF_bypass);
	pt.put("HF Bypass", tmp);
	pt.put("HF", m_HF_flowrate);
	tmp = bypass_to_string(m_EtOH_bypass);
	pt.put("EtOH Bypass", tmp);
	pt.put("EtOH", m_EtOH_flowrate);
	pt.put("N2", m_N2_flowrate);
	pt.put("N2 Purge", m_N2_purge_flowrate);
}


Recipe::Recipe(const Recipe& rhs)
{
	m_name = rhs.m_name;
	m_steps = rhs.m_steps;
}

Recipe& Recipe::operator = (const Recipe& rhs)
{
	m_name = rhs.m_name;
	m_steps = rhs.m_steps;

	return *this;
}

void Recipe::Load(const std::string& name)
{
	ptree pt;
	try
	{
		std::string recipe_name = "./recipe/" + name + ".rcp";
		json_parser::read_json(recipe_name, pt);
		m_steps.clear();
		for(ptree::value_type &v : pt.get_child("Steps"))
		{
			RecipeStep step;
			step.Load(v.second);
			m_steps.push_back(step);
		}
		m_name = name;
	}
	catch(...)
	{
		//TODO::report system event
		Reset();
	}
}

void Recipe::LoadFromString(const std::string& name, const std::string& recipe)
{
	ptree pt;
	try
	{
		std::istringstream ss(recipe);
		json_parser::read_json(ss, pt);
		m_steps.clear();
		for(ptree::value_type &v : pt.get_child("Steps"))
		{
			RecipeStep step;
			step.Load(v.second);
			m_steps.push_back(step);
		}
		m_name = name;
	}
	catch(...)
	{
		//TODO::report system event
		Reset();
	}
}

void Recipe::Save()
{
	if(m_name.empty() || m_steps.empty())
		return;

	ptree pt;
	for(RecipeStep& step : m_steps)
	{
		ptree step_pt;
		step.Save(step_pt);
		pt.push_back(std::make_pair("", step_pt));
	}

	ptree root;
	root.add_child("Steps", pt);

	json_parser::write_json(recipe_fullname(m_name), root);
}

void Recipe::Reset()
{
	m_name.clear();
	m_steps.clear();
}

