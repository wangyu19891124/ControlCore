/*
 * Recipe.cpp
 *
 *  Created on: 2014Äê3ÔÂ19ÈÕ
 *      Author: acm
 */

#include "Recipe.h"
#include "Utility.h"

using namespace boost::property_tree;

RecipeStep::RecipeStep(const RecipeStep& rhs) : RecipeStep(rhs.m_name, rhs.m_N2_flowrate, rhs.m_EtOH_flowrate,
		rhs.m_HF_flowrate, rhs.m_duration, rhs.m_pressure)
{
}

RecipeStep& RecipeStep::operator = (const RecipeStep& rhs)
{
	m_name = rhs.m_name;
	m_N2_flowrate = rhs.m_N2_flowrate;
	m_EtOH_flowrate = rhs.m_EtOH_flowrate;
	m_HF_flowrate = rhs.m_HF_flowrate;
	m_duration = rhs.m_duration;
	m_pressure = rhs.m_pressure;

	return *this;
}

void RecipeStep::Load(const boost::property_tree::ptree& pt)
{
	m_name = pt.get<std::string>(ptree::path_type("Name"));
	m_N2_flowrate = pt.get<int>(ptree::path_type("N2"));
	m_EtOH_flowrate = pt.get<int>(ptree::path_type("EtOH"));
	m_HF_flowrate = pt.get<int>(ptree::path_type("HF"));
	m_duration = pt.get<float>(ptree::path_type("Time"));
	m_pressure = pt.get<int>(ptree::path_type("Pressure"));
}

void RecipeStep::Save(boost::property_tree::ptree& pt)
{
	pt.put(ptree::path_type("Name"), m_name);
	pt.put(ptree::path_type("N2"), m_N2_flowrate);
	pt.put(ptree::path_type("EtOH"), m_EtOH_flowrate);
	pt.put(ptree::path_type("HF"), m_HF_flowrate);
	pt.put(ptree::path_type("Time"), m_duration);
	pt.put(ptree::path_type("Pressure"), m_pressure);
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
		m_name = name;
		m_steps.clear();
		for(ptree::value_type &v : pt.get_child("Steps"))
		{
			RecipeStep step;
			step.Load(v.second);
			m_steps.push_back(step);
		}
	}
	catch(...)
	{
		//TODO::report system event
		m_name.clear();
		m_steps.clear();
		return;
	}
}

void Recipe::LoadFromString(const std::string& name, const std::string& recipe)
{
	ptree pt;
	try
	{
		std::istringstream ss(recipe);
		json_parser::read_json(ss, pt);
		m_name = name;
		m_steps.clear();
		for(ptree::value_type &v : pt.get_child("Steps"))
		{
			RecipeStep step;
			step.Load(v.second);
			m_steps.push_back(step);
		}
	}
	catch(...)
	{
		//TODO::report system event
		Reset();
		return;
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

