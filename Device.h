/*
 * Device.h
 *
 *  Created on: 2014Äê2ÔÂ27ÈÕ
 *      Author: acm
 */

#ifndef DEVICE_H_
#define DEVICE_H_

#include <map>
#include <vector>

#include "boost/function.hpp"
#include "boost/thread/recursive_mutex.hpp"

class Device
{
public:
	Device(int dev_id) : m_dev_id(dev_id) {};
	virtual ~Device() = default;

	virtual bool IsSimulator();

	virtual std::string GetName() = 0;
	virtual void Initialize() = 0;
	virtual void Terminate() = 0;
	//for real device
	virtual void Write(unsigned value, unsigned block, unsigned io_offset, unsigned bit_offset, unsigned bits) = 0;
	virtual unsigned Read(unsigned block, unsigned io_offset, unsigned bit_offset, unsigned bits) = 0;
	//for simulator
	virtual void Write(int id, float value) = 0;
	virtual float Read(int id) = 0;

	unsigned int Follow(unsigned block, boost::function<void ()> f);
	void Unfollow(unsigned token);

protected:
	void Notify(unsigned block);

private:
	std::map<unsigned, std::vector<boost::function<void ()> > > m_follower;
	boost::recursive_mutex m_mtx;
	int m_dev_id;
};

#endif /* DEVICE_H_ */
