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
	Device();
	virtual ~Device();

	virtual std::string GetName() = 0;
	virtual void Initialize() = 0;
	virtual void Write(unsigned value, unsigned block, unsigned io_offset, unsigned bit_offset, unsigned bits) = 0;
	virtual unsigned Read(unsigned block, unsigned io_offset, unsigned bit_offset, unsigned bits) = 0;
	virtual void Terminate() = 0;

	virtual unsigned int Follow(unsigned block, boost::function<void ()> f);
	virtual void Unfollow(unsigned token);

protected:
	void Notify(unsigned block);

private:
	std::map<unsigned, std::vector<boost::function<void ()> > > m_follower;
	boost::recursive_mutex m_mtx;
};

#endif /* DEVICE_H_ */
