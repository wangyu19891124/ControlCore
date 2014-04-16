/*
 * ParameterItem.h
 *
 *  Created on: 2014Äê3ÔÂ17ÈÕ
 *      Author: acm
 */

#ifndef PARAMETERITEM_H_
#define PARAMETERITEM_H_

#include <set>

#include "boost/property_tree/ptree.hpp"

#include "ParameterHolder.h"

class ParameterItemBase
{
public:
	ParameterItemBase(int id, const std::string& name, const std::string& path,
			const std::string& description, const std::string& unit = "");
	ParameterItemBase() = delete;
	ParameterItemBase(const ParameterItemBase&) = delete;
	virtual ~ParameterItemBase(){};
	ParameterItemBase& operator = (const ParameterItemBase&) = delete;

	bool IsChild(const std::string& path);
	bool IsInRange(int from, int to);
	bool IsInSet(const std::set<int>& id_set);

	virtual void Serialize(boost::property_tree::ptree& pt) = 0;

protected:
	int m_id;
	std::string m_name;
	std::string m_path;
	std::string m_description;
	std::string m_unit;
	boost::mutex m_mtx;
};

template<typename T>
class ParameterItem : public ParameterItemBase
{
public:
	ParameterItem(int id, const std::string& name,  const std::string& path,const std::string& description,
			T min_value, T max_value, T default_value, const std::string& unit = "")
		: ParameterItemBase(id, path, name, description, unit), m_min(min_value), m_max(max_value), m_default(default_value)
	{
		m_value = ParameterHolder::Instance().Read<T>(path, name, default_value);
	}
	~ParameterItem(void){};

public:
	operator T()
	{
		return m_value;
	}

	T operator = (const T& rhs)
	{
		if(rhs>m_max || rhs<m_min)
		{
			//report warning...
		}
		else
		{
			{
				boost::mutex::scoped_lock lock(m_mtx);
				m_value = rhs;
			}
			ParameterHolder::Instance().Write<T>(m_path, m_name, rhs);
		}

		return rhs;
	}

	virtual void Serialize(boost::property_tree::ptree& pt)
	{
		using namespace boost::property_tree;
		ptree node;
		node.add<int>("id", m_id);
		node.add<T>("value", m_value);
		pt.push_back(make_pair("", node));
	}

private:
	T m_min;
	T m_max;
	T m_default;
	T m_value;
};

template<>
class ParameterItem<std::string> : public ParameterItemBase
{
public:
	ParameterItem(int id, const std::string& name, const std::string& path, const std::string& description, std::string default_value)
		: ParameterItemBase(id, path, description, ""), m_default(default_value)
	{
		m_value = ParameterHolder::Instance().Read<std::string>(path, name, default_value);
	}
	~ParameterItem(void){};

public:
	operator std::string()
	{
		std::string str;
		{
			boost::mutex::scoped_lock lock(m_mtx);
			str = m_value;
		}

		return str;
	}

	ParameterItem& operator = (const std::string& rhs)
	{
		{
			boost::mutex::scoped_lock lock(m_mtx);
			m_value = rhs;
		}
		ParameterHolder::Instance().Write(m_path, m_name, rhs);

		return *this;
	}

	virtual void Serialize(boost::property_tree::ptree& pt)
	{
		using namespace boost::property_tree;
		ptree node;
		node.add<int>("id", m_id);
		node.add("value", m_value);
		pt.push_back(make_pair("", node));
	}

private:
	std::string m_default;
	std::string m_value;
};



#endif /* PARAMETERITEM_H_ */
