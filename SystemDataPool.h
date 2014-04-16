/*
 * SystemDataPool.h
 *
 *  Created on: 2014Äê3ÔÂ5ÈÕ
 *      Author: acm
 */

#ifndef SYSTEMDATAPOOL_H_
#define SYSTEMDATAPOOL_H_

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"

#include "SystemData.h"
#include "Singleton.h"

class SystemDataPool : public SingletonT<SystemDataPool>
{
protected:
	SystemDataPool() = default;
public:
	virtual ~SystemDataPool() = default;

	void Initialize();
	void Terminate();
	std::string GetJsonData(boost::function<bool (BaseSystemData*)> f);

	friend class SingletonT<SystemDataPool>;

private:
	void InitializeData(BaseSystemData& data)
	{
		data.Initialize();
		m_all_data[data.GetID()] = &data;
	}

	void TerminateData(BaseSystemData& data)
	{
		m_all_data[data.GetID()] = nullptr;
		data.Terminate();
	}

private:
	std::map<int, BaseSystemData*> m_all_data;
};

#endif /* SYSTEMDATAPOOL_H_ */
