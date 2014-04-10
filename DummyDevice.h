/*
 * DummyDevice.h
 *
 *  Created on: 2014Äê4ÔÂ7ÈÕ
 *      Author: Administrator
 */

#ifndef DUMMYDEVICE_H_
#define DUMMYDEVICE_H_

#include "Device.h"

class DummyDevice: public Device
{
public:
	DummyDevice(int dev_id) : Device(dev_id){};
	virtual ~DummyDevice() = default;

	virtual std::string GetName();
	virtual void Initialize();
	virtual void Terminate();
	//for real device
	virtual void Write(unsigned value, unsigned block, unsigned io_offset, unsigned bit_offset, unsigned bits);
	virtual unsigned Read(unsigned block, unsigned io_offset, unsigned bit_offset, unsigned bits);
	//for simulator
	virtual void Write(int id, float value);
	virtual float Read(int id);
};

#endif /* DUMMYDEVICE_H_ */
