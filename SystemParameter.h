/*
 * SystemParameter.h
 *
 *  Created on: 2014Äê3ÔÂ17ÈÕ
 *      Author: acm
 */

#ifndef SYSTEMPARAMETER_H_
#define SYSTEMPARAMETER_H_

#include "ParameterItem.h"

template<typename T>
class ParameterItem;

class SystemParameter : public SingletonT<SystemParameter>
{
protected:
	SystemParameter() = default;

	SystemParameter(const SystemParameter&) = delete;
	SystemParameter& operator = (const SystemParameter&) = delete;
public:
	~SystemParameter() = default;

	void Mapping(int id, ParameterItemBase* cfg_ptr)
	{
		m_cfgs[id] = cfg_ptr;
	}

	template<typename T>
	void SetData(int id, const T& data)
	{
		ParameterItem<T>* p = dynamic_cast<ParameterItem<T>*>(m_cfgs[id]);
		if(p)
			*p = data;
	}

	template<typename T>
	T GetData(int id)
	{
		ParameterItem<T>* p = dynamic_cast<ParameterItem<T>*>(m_cfgs[id]);
		if(p)
			return (T)(*p);

		return T();
	}

	std::string GetJsonData(boost::function<bool (ParameterItemBase*)> f)
	{
		using namespace boost::property_tree;
		ptree array;
		ParameterItemBase* item_ptr = nullptr;
		for(auto &v : m_cfgs)
		{
			item_ptr = v.second;
			if(f && f(item_ptr))
			{
				item_ptr->Serialize(array);
			}
		}
		ptree pt;
		pt.add_child("parameters", array);

		std::stringstream ss;
		json_parser::write_json(ss, pt);

		return ss.str();
	}

	friend class SingletonT<SystemParameter>;

protected:
	std::map<int, ParameterItemBase*> m_cfgs;
};


#endif /* SYSTEMPARAMETER_H_ */
