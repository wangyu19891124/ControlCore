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

class RecipeStep
{
public:
	RecipeStep(const std::string& name, int N2flow, int EtOHflow, int HFflow, float duration, int pressure)
	: m_name(name), m_N2_flowrate(N2flow), m_EtOH_flowrate(EtOHflow), m_HF_flowrate(HFflow),
	  m_duration(duration), m_pressure(pressure) {};
	RecipeStep() : RecipeStep("", 0, 0, 0, 0.0f, 0){};
	RecipeStep(const RecipeStep& rhs);
	RecipeStep& operator = (const RecipeStep& rhs);

	void Load(const boost::property_tree::ptree& pt);
	void Save(boost::property_tree::ptree& pt);

	const std::string& Name() const
	{
		return m_name;
	}

	int N2Flowrate() const
	{
		return m_N2_flowrate;
	}

	int EtOHFlowrate() const
	{
		return m_EtOH_flowrate;
	}

	int HFFlowrate() const
	{
		return m_HF_flowrate;
	}

	float Duration() const
	{
		return m_duration;
	}

	int Pressure() const
	{
		return m_pressure;
	}

protected:
	std::string m_name;
	int m_N2_flowrate;
	int m_EtOH_flowrate;
	int m_HF_flowrate;
	float m_duration;
	int m_pressure;
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

	float Duration()
	{
		float dur = .0f;
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
