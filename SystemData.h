/*
 * SystemData.h
 *
 *  Created on: 2014��2��25��
 *      Author: acm
 */

#ifndef SYSTEMDATA_H_
#define SYSTEMDATA_H_

#include <string>
#include <typeinfo>

#include "boost/property_tree/ptree.hpp"
#include "boost/function.hpp"
#include "boost/thread/mutex.hpp"

#include "DeviceManager.h"
#include "Worker.h"

const int NoRelatedDevice = -1;

//typedef boost::function<unsigned int (const std::vector<unsigned char>&)> ReadFunc;
//typedef boost::function<void (std::vector<unsigned char>&, unsigned int)> WriteFunc;
template<typename T>
T DefaultDataConvert(T data)
{
	return data;
}

template<typename T1, typename T2>
T1 MemeryDataConvert(T2 data)
{
	static_assert(sizeof(T1) == sizeof(T2), "The size of T1 and T2 are different in MemeryDataConvert.");

	T1 t;
	memcpy_s(&t, &data, sizeof(T1));
	return t;
}

template<typename T1, typename T2>
T1 StaticDataConvert(T2 data)
{
	return static_cast<T1>(data);
}

class BaseSystemData
{
public:
	BaseSystemData(int id, const std::string& name,
			const std::string& path);
	virtual ~BaseSystemData();

	virtual void Serialize(boost::property_tree::ptree& pt) = 0;
	virtual const std::type_info& GetType() = 0;
	virtual void Initialize() = 0;
	virtual void Terminate() = 0;

	int GetID()
	{
		return m_id;
	}

protected:
	int m_id;
	std::string m_name;
	std::string m_path;
};

template<typename T>
class SystemData : public BaseSystemData
{
public:
	SystemData(int id, const std::string& name, const std::string& path, T min, T max, int precision, int device,
			unsigned int block, unsigned int io_offset, unsigned short bit_offset,
			unsigned short bits, bool writable, const std::string& unit = "",
			boost::function<T (unsigned int)> raw_to_real = DefaultDataConvert<unsigned int>,
			boost::function<unsigned int (T)> real_to_raw = DefaultDataConvert<unsigned int>)
	: BaseSystemData(id, name, path), m_unit(unit), m_min(min), m_max(max), m_precision(precision), m_device(device),
	  m_block(block), m_io_offset(io_offset), m_bit_offset(bit_offset), m_bits(bits), m_writable(writable), m_data(T()),
	  m_token(0), m_raw_to_real(raw_to_real), m_real_to_raw(real_to_raw){};

	SystemData(int id, const std::string& name, const std::string& path, T min, T max, int precision =0, const std::string& unit = "")
	: SystemData(id, name, path, min, max, precision, NoRelatedDevice, 0, 0, 0, 0, true, unit){};

	virtual ~SystemData(){};

	operator T()
	{
		return m_data;
	}

	SystemData& operator = (const T& rhs)
	{
		if(!m_writable)
		{
			std::stringstream ss;
			ss<<m_name<<" can't be written.";
			throw ss.str();
		}

		if(rhs<=m_max && rhs>=m_min)
		{
			boost::mutex::scoped_lock lock(m_mtx);
			m_data = rhs;
		}
		else
		{
			//TODO comment the 3 line after debugging.
			std::stringstream ss;
			ss<<m_name<<" is assigned "<<rhs<<", it's out of range ["<<m_min<<", "<<m_max<<"].";
			throw ss.str();
		}

		for(boost::function<bool (T)> &f : m_precheck_funcs)
		{
			if(f(rhs))
				return *this;
		}

		WriteData();

		return *this;
	}

	virtual void Serialize(boost::property_tree::ptree& pt)
	{
		using namespace boost::property_tree;
		ptree node;
		node.add<int>("<xmlattr>.id", m_id);
		node.add<T>("<xmlattr>.value", m_data);
		pt.add_child("SystemData.Data", node);
	}

	virtual const std::type_info& GetType()
	{
		return typeid(T);
	}

	virtual void Initialize()
	{
		if(m_id == NoRelatedDevice)
			return;

		Device& dev = DeviceManager::Instance().GetDevice(m_id);
		m_get_func = boost::bind(&Device::Read, &dev, m_block, m_io_offset, m_bit_offset, m_bits);
		ReadData();
		if(m_writable)
			m_put_func = boost::bind(&Device::Write, &dev, _1, m_block, m_io_offset, m_bit_offset, m_bits);
		else
			m_token = dev.Follow(m_block, boost::bind(&SystemData<T>::ReadData, this));
	}

	virtual void Terminate()
	{
		if(m_id == NoRelatedDevice)
			return;

		if(m_writable)
			m_put_func.clear();
		else
		{
			Device& dev = DeviceManager::Instance().GetDevice(m_id);
			dev.Unfollow(m_token);
		}
	}

	void AddPrecheck(boost::function<bool (T)> checker)
	{
		m_precheck_funcs.push_back(checker);
	}

	unsigned int AddUpdateSink(boost::function<void (T)> sink)
	{
		boost::mutex::scoped_lock lock(m_mtx);
		unsigned int i=0;
		for(boost::function<void (T)>& v : m_update_sinks)
		{
			if(v)
			{
				++i;
			}
			else
			{
				v = sink;
				break;
			}
		}
		if(i == m_update_sinks.size())
			m_update_sinks.push_back(sink);

		return i;
	}

	void RemoveUpdateSink(unsigned int token)
	{
		boost::mutex::scoped_lock lock(m_mtx);
		if(token >= m_update_sinks.size())
			return;

		m_update_sinks[token] = nullptr;
	}

private:
	void WriteData()
	{
		if(m_put_func)
		{
			unsigned int raw = 0;
			raw = m_real_to_raw(m_data);

			m_put_func(raw);
		}
	}

	void ReadData()
	{
		unsigned int raw = 0;
		if(m_get_func)
			raw = m_get_func();

		m_data = m_raw_to_real(raw);

		boost::mutex::scoped_lock lock(m_mtx);
		for(boost::function<void (T)>& f : m_update_sinks)
		{
			if(f)
				Worker::Instance().Post(boost::bind(f, m_data));
		}
	}

private:
	std::string m_unit;
	T m_min;
	T m_max;
	int m_precision;
	int m_device;
	unsigned int m_block;
	unsigned int m_io_offset;
	unsigned short m_bit_offset;
	unsigned short m_bits;
	bool m_writable;
	T m_data;
	unsigned int m_token;
	boost::function<T (unsigned int)> m_raw_to_real;
	boost::function<unsigned int (T)> m_real_to_raw;

	boost::function<unsigned int ()> m_get_func;
	boost::function<void (unsigned int)> m_put_func;

	std::vector<boost::function<bool (T)>> m_precheck_funcs;
	std::vector<boost::function<void (T)>> m_update_sinks;

	boost::mutex m_mtx;
};

template<>
class SystemData<std::string> : public BaseSystemData
{
public:
	SystemData(int id, const std::string& name, const std::string& path)
	: BaseSystemData(id, name, path){};

	virtual ~SystemData(){};

	operator std::string()
	{
		return m_data;
	}

	SystemData& operator = (const std::string& rhs)
	{
		boost::mutex::scoped_lock lock(m_mtx);
		m_data = rhs;
		return *this;
	}

	virtual void Serialize(boost::property_tree::ptree& pt)
	{
		using namespace boost::property_tree;
		ptree node;
		node.add<int>("<xmlattr>.id", m_id);
		node.add<std::string>("<xmlattr>.value", m_data);
		pt.add_child("SystemData.Data", node);
	}

	virtual const std::type_info& GetType()
	{
		return typeid(std::string);
	}

	virtual void Initialize()
	{

	}

	virtual void Terminate()
	{

	}

private:
	std::string m_data;
	boost::mutex m_mtx;
};


#endif /* SYSTEMDATA_H_ */
