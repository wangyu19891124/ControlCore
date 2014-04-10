/*
 * AdsDevice.h
 *
 *  Created on: 2014Äê4ÔÂ8ÈÕ
 *      Author: Administrator
 */

#ifndef ADSDEVICE_H_
#define ADSDEVICE_H_

#include <map>

#include "boost/shared_ptr.hpp"

#include "Device.h"

class AdsDevice : public Device
{
public:
	AdsDevice(int dev_id) : Device(dev_id){};
	virtual ~AdsDevice() = default;

	virtual std::string GetName();
	virtual void Initialize();
	virtual void Terminate();
	//for real device
	virtual void Write(unsigned value, unsigned block, unsigned io_offset, unsigned bit_offset, unsigned bits);
	virtual unsigned Read(unsigned block, unsigned io_offset, unsigned bit_offset, unsigned bits);
	//for simulator
	virtual void Write(int id, float value);
	virtual float Read(int id);

private:
	std::map<int, boost::shared_ptr<AdsBlock>> m_blocks;
};

#endif /* ADSDEVICE_H_ */
