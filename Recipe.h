/*
 * Recipe.h
 *
 *  Created on: 2014Äê3ÔÂ19ÈÕ
 *      Author: acm
 */

#ifndef RECIPE_H_
#define RECIPE_H_

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"

enum APCMode
{
	APCMode_Position,
	APCMode_Pressure,
};

enum BypassMode
{
	BypassMode_None,
	BypassMode_Bypass,
	BypassMode_Chamber,
};

class RecipeStep
{
public:
	RecipeStep(const std::string& name, unsigned short duration, APCMode apc_mode, unsigned short position,
			unsigned short pressure, unsigned short rotate_speed, BypassMode HF_bypass,
			unsigned short HF_flow, BypassMode EtOH_bypass, unsigned short EtOH_flow, unsigned short N2_flow,
			unsigned short N2_purge_flow)
	: m_name(name), m_duration(duration), m_apc_mode(apc_mode), m_position(position), m_pressure(pressure),
	  m_rotate_speed(rotate_speed), m_HF_bypass(HF_bypass), m_HF_flowrate(HF_flow), m_EtOH_bypass(EtOH_bypass),
	  m_EtOH_flowrate(EtOH_flow), m_N2_flowrate(N2_flow), m_N2_purge_flowrate(N2_purge_flow) {};
	RecipeStep() : RecipeStep("", 0, APCMode_Position, 0, 0, 0, BypassMode_None, 0, BypassMode_None, 0, 0, 0){};
	RecipeStep(const RecipeStep& rhs) : RecipeStep(rhs.m_name, rhs.m_duration, rhs.m_apc_mode,
			rhs.m_position, rhs.m_pressure, rhs.m_rotate_speed, rhs.m_HF_bypass, rhs.m_HF_flowrate,
			rhs.m_EtOH_bypass, rhs.m_EtOH_flowrate, rhs.m_N2_flowrate, rhs.m_N2_purge_flowrate) {};
	RecipeStep& operator = (const RecipeStep& rhs);

	void Load(const boost::property_tree::ptree& pt);
	void Save(boost::property_tree::ptree& pt);

	const std::string& Name() const
	{
		return m_name;
	}

	unsigned short Duration() const
	{
		return m_duration;
	}

	APCMode Mode() const
	{
		return m_apc_mode;
	}

	unsigned short Position() const
	{
		return m_position;
	}

	unsigned short Pressure() const
	{
		return m_pressure;
	}

	unsigned short RotateSpeed() const
	{
		return m_rotate_speed;
	}

	BypassMode HFBypass() const
	{
		return m_HF_bypass;
	}

	unsigned short HFFlowrate() const
	{
		return m_HF_flowrate;
	}

	BypassMode EtOHBypass() const
	{
		return m_EtOH_bypass;
	}

	unsigned short EtOHFlowrate() const
	{
		return m_EtOH_flowrate;
	}

	unsigned short N2Flowrate() const
	{
		return m_N2_flowrate;
	}

	unsigned short N2PurgeFlowrate() const
	{
		return m_N2_purge_flowrate;
	}

private:
	static BypassMode bypass_from_string(const std::string& mode);
	static std::string bypass_to_string(BypassMode mode);
	static APCMode apc_from_string(const std::string& mode);
	static std::string apc_to_string(APCMode mode);

protected:
	std::string m_name;
	unsigned short m_duration;
	APCMode m_apc_mode;
	unsigned short m_position;
	unsigned short m_pressure;
	unsigned short m_rotate_speed;
	BypassMode m_HF_bypass;
	unsigned short m_HF_flowrate;
	BypassMode m_EtOH_bypass;
	unsigned short m_EtOH_flowrate;
	unsigned short m_N2_flowrate;
	unsigned short m_N2_purge_flowrate;
};

class Recipe
{
public:
	Recipe() = default;
	virtual ~Recipe() = default;

	Recipe(const Recipe& rhs);
//	Recipe(Recipe&& rhs);
	Recipe& operator = (const Recipe& rhs);
//	Recipe&& operator = (Recipe&& rhs);

	void Load(const std::string& name);
	void LoadFromString(const std::string& name, const std::string& recipe);
	void Save();
	void Reset();

	std::string Name()
	{
		return m_name;
	}

	unsigned short Duration()
	{
		unsigned short dur = 0;
		for(RecipeStep& step : m_steps)
		{
			dur += step.Duration();
		}

		return dur;
	}

	unsigned TotalStep()
	{
		return m_steps.size();
	}

	const RecipeStep& Step(unsigned index)
	{
		if(index >= m_steps.size())
		{
			throw "Wrong index of recipe step.";
		}

		return m_steps[index];
	}

protected:
	std::string m_name;
	std::vector<RecipeStep> m_steps;
};

#endif /* RECIPE_H_ */
