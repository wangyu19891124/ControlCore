/*
 * DummyDevice.cpp
 *
 *  Created on: 2014Äê4ÔÂ7ÈÕ
 *      Author: Administrator
 */

#include "DummyDevice.h"

void DummyDevice::Initialize()
{
}

void DummyDevice::Terminate()
{
}

std::string DummyDevice::GetName()
{
	return "Dummy";
}

//for real device
void DummyDevice::Write(unsigned int value, unsigned block, unsigned io_offset,
		unsigned bit_offset, unsigned bits)
{

}

unsigned int DummyDevice::Read(unsigned block, unsigned io_offset, unsigned bit_offset, unsigned bits)
{
	return 0;
}
