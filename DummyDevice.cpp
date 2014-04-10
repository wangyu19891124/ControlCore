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
void DummyDevice::Write(unsigned value, unsigned block, unsigned io_offset,
		unsigned bit_offset, unsigned bits)
{

}

unsigned DummyDevice::Read(unsigned block, unsigned io_offset, unsigned bit_offset, unsigned bits)
{
	return 0;
}

//for simulator
void DummyDevice::Write(int id, float value)
{

}

float DummyDevice::Read(int id)
{
	return 0.0f;
}
