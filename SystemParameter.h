/*
 * SystemParameter.h
 *
 *  Created on: 2014Äê3ÔÂ17ÈÕ
 *      Author: acm
 */

#ifndef SYSTEMPARAMETER_H_
#define SYSTEMPARAMETER_H_

class ParameterItemBase;

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

	std::string GetJsonData(const std::string& path)
	{
		return ParameterHolder::Instance().ToJson(path);
	}

	friend class SingletonT<SystemParameter>;

protected:
	std::map<int, ParameterItemBase*> m_cfgs;
};


#endif /* SYSTEMPARAMETER_H_ */
