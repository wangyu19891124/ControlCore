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
	virtual void Write(unsigned long long value, unsigned block, unsigned byte_offset, unsigned bit_offset, unsigned bits);
	virtual unsigned long long Read(unsigned block, unsigned byte_offset, unsigned bit_offset, unsigned bits);
};

#endif /* DUMMYDEVICE_H_ */
