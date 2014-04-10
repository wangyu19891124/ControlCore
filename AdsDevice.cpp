/*
 * AdsDevice.cpp
 *
 *  Created on: 2014Äê4ÔÂ8ÈÕ
 *      Author: Administrator
 */

#include "boost/regex.hpp"

#include "AdsDevice.h"

void AdsDevice::Initialize()
{
	ConfigFile cfg("ads");
	std::string ams_net_id = cfg.Read<std::string>("AmsNetID", "192.168.3.100.1.1");
	std::string heater_net_id = cfg.Read<std::string>("HeaterNetID", "192.168.3.100.1.1");

	ams_addr_from_string(m_ams_addr, ams_net_id);
}

void AdsDevice::Terminate()
{

}

std::string AdsDevice::GetName()
{
	return "Ads";
}

//for real device
void AdsDevice::Write(unsigned value, unsigned block, unsigned io_offset,
		unsigned bit_offset, unsigned bits)
{

}

unsigned AdsDevice::Read(unsigned block, unsigned io_offset, unsigned bit_offset, unsigned bits)
{
	return 0;
}

//for simulator
void AdsDevice::Write(int id, float value)
{

}

float AdsDevice::Read(int id)
{
	return 0.0f;
}
