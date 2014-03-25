/*
 * ParameterItem.h
 *
 *  Created on: 2014Äê3ÔÂ17ÈÕ
 *      Author: acm
 */

#ifndef PARAMETERITEM_H_
#define PARAMETERITEM_H_

#include "ParameterHolder.h"
#include "SystemParameter.h"

class ParameterItemBase
{
public:
	ParameterItemBase(int id, const std::string& path, const std::string& description, const std::string& unit = "")
	: m_description(description), m_unit(unit)
	{
		m_path = "Parameter/" + path;
		SystemParameter::Instance().Mapping(id, this);
	}
	ParameterItemBase() = delete;
	ParameterItemBase(const ParameterItemBase&) = delete;
	virtual ~ParameterItemBase(){};
	ParameterItemBase& operator = (const ParameterItemBase&) = delete;

	const std::string& GetPath()
	{
		return m_path;
	}

protected:
	std::string m_path;
	std::string m_description;
	std::string m_unit;
	boost::mutex m_mtx;
};

template<typename T>
class ParameterItem : public ParameterItemBase
{
public:
	ParameterItem(int id, const std::string& path, const std::string& description,
			T min_value, T max_value, T default_value, const std::string& unit = "")
		: ParameterItemBase(id, path, description, unit), m_min(min_value), m_max(max_value), m_default(default_value)
	{
		m_value = ParameterHolder::Instance().Read<T>(path, default_value);
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
			ParameterHolder::Instance().Write<T>(m_path, rhs);
		}

		return rhs;
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
	ParameterItem(int id, const std::string& path, const std::string& description, std::string default_value)
		: ParameterItemBase(id, path, description, ""), m_default(default_value)
	{
		m_value = ParameterHolder::Instance().Read<std::string>(path, default_value);
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
		ParameterHolder::Instance().Write(m_path, rhs);

		return *this;
	}

private:
	std::string m_default;
	std::string m_value;
};



#endif /* PARAMETERITEM_H_ */
