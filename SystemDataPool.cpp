/*
 * SystemDataPool.cpp
 *
 *  Created on: 2014Äê3ÔÂ5ÈÕ
 *      Author: acm
 */

#include "SystemDataPool.h"
#include "Data.h"

void SystemDataPool::Initialize()
{
    InitializeData(Data::diAlcPrsULmt);
    InitializeData(Data::diAlcPrsLLmt);
    InitializeData(Data::diAlcTkPrsULmt);
    InitializeData(Data::diAlcTkPrsLLmt);
    InitializeData(Data::diHFSplPrsULmt);
    InitializeData(Data::diHFSplPrsLLmt);
    InitializeData(Data::diN2PgHFPrsULmt);
    InitializeData(Data::diN2PgHFPrsLLmt);
    InitializeData(Data::diN2PgAlcTkPrsULmt);
    InitializeData(Data::diN2PgAlcTkPrsLLmt);
    InitializeData(Data::diN2PgExpCbPrsULmt);
    InitializeData(Data::diN2PgExpCbPrsLLmt);
    InitializeData(Data::diN2SplVPumpPrsULmt);
    InitializeData(Data::diN2SplVPumpPrsLLmt);
    InitializeData(Data::diN2PgPrcCbPrsULmt);
    InitializeData(Data::diN2PgPrcCbPrsLLmt);
    InitializeData(Data::diN2FacSplPrsULmt);
    InitializeData(Data::diN2FacSplPrsLLmt);
    InitializeData(Data::diN2PgVapPrsULmt);
    InitializeData(Data::diN2PgVapPrsLLmt);
    InitializeData(Data::diCDAInletAlarm);
    InitializeData(Data::diFacVPrsSwtLLmt);
    InitializeData(Data::diExpCbVPrsSwtULmt);
    InitializeData(Data::diExpCbVPrsSwtLLmt);
    InitializeData(Data::diIODoorClose);
    InitializeData(Data::diPCDoorClose);
    InitializeData(Data::diPneuDoorClose);
    InitializeData(Data::diAcFrmDoorClose);
    InitializeData(Data::diAcDoorOverride);
    InitializeData(Data::diVaporMHeaterAlarm);
    InitializeData(Data::diVaporVHeaterAlarm);
    InitializeData(Data::diHFReady);
    InitializeData(Data::diHeartbeatFail);
    InitializeData(Data::diExhaustAlarm);
    InitializeData(Data::diFacInletVPrsULmt);
    InitializeData(Data::diAlcoholLeak);
    InitializeData(Data::diPrcCbVacuum);
    InitializeData(Data::diPrcCbDoorClose);
    InitializeData(Data::diAlcoholGasLeak);
    InitializeData(Data::diGasboxDoorClose);
    InitializeData(Data::diDoorOverride);
    InitializeData(Data::diInterlockReset);
    InitializeData(Data::diHFLeak);
    InitializeData(Data::diThrottleValveOpen);
    InitializeData(Data::diHWInterlock);
    InitializeData(Data::diAlcTkLow);
    InitializeData(Data::diAlcTkHigh);
    InitializeData(Data::diAlcTkHighHigh);
    InitializeData(Data::diAlcTkOverfill);
    InitializeData(Data::diVPumpWarning);
    InitializeData(Data::diVPumpAlarm);

    InitializeData(Data::diPrcCbDoorOpen);
    InitializeData(Data::diWaferPickUp);
    InitializeData(Data::diWaferPickDown);
    InitializeData(Data::diWaferClamp);
    InitializeData(Data::diWaferUnclamp);
    InitializeData(Data::diArmInPos);
    InitializeData(Data::diArmOutPos);
    InitializeData(Data::diPrcCbLidLeftOpen);
    InitializeData(Data::diPrcCbLidLeftClose);
    InitializeData(Data::diPrcCbLidRightOpen);
    InitializeData(Data::diPrcCbLidRightClose);
    InitializeData(Data::diCbLeftDoorClose);
    InitializeData(Data::diCbRightDoorClose);

//DO
    InitializeData(Data::aoRedLight);
    InitializeData(Data::aoYellowLight);
    InitializeData(Data::aoGreenLight);
    InitializeData(Data::aoBlueLight);
    InitializeData(Data::aoBuzzer);
    InitializeData(Data::doHeartbeat);
    InitializeData(Data::doEnableVPump);
    InitializeData(Data::doHFRequest);
    InitializeData(Data::doExpCbVacValve);
    InitializeData(Data::doExpCbVapVacValve);
    InitializeData(Data::doAlcMFCBypassValve1);


    InitializeData(Data::flag);
}

void SystemDataPool::Terminate()
{
    TerminateData(Data::diAlcPrsULmt);
    TerminateData(Data::diAlcPrsLLmt);
    TerminateData(Data::diAlcTkPrsULmt);
    TerminateData(Data::diAlcTkPrsLLmt);
    TerminateData(Data::diHFSplPrsULmt);
    TerminateData(Data::diHFSplPrsLLmt);
    TerminateData(Data::diN2PgHFPrsULmt);
    TerminateData(Data::diN2PgHFPrsLLmt);
    TerminateData(Data::diN2PgAlcTkPrsULmt);
    TerminateData(Data::diN2PgAlcTkPrsLLmt);
    TerminateData(Data::diN2PgExpCbPrsULmt);
    TerminateData(Data::diN2PgExpCbPrsLLmt);
    TerminateData(Data::diN2SplVPumpPrsULmt);
    TerminateData(Data::diN2SplVPumpPrsLLmt);
    TerminateData(Data::diN2PgPrcCbPrsULmt);
    TerminateData(Data::diN2PgPrcCbPrsLLmt);
    TerminateData(Data::diN2FacSplPrsULmt);
    TerminateData(Data::diN2FacSplPrsLLmt);
    TerminateData(Data::diN2PgVapPrsULmt);
    TerminateData(Data::diN2PgVapPrsLLmt);
    TerminateData(Data::diCDAInletAlarm);
    TerminateData(Data::diFacVPrsSwtLLmt);
    TerminateData(Data::diExpCbVPrsSwtULmt);
    TerminateData(Data::diExpCbVPrsSwtLLmt);
    TerminateData(Data::diIODoorClose);
    TerminateData(Data::diPCDoorClose);
    TerminateData(Data::diPneuDoorClose);
    TerminateData(Data::diAcFrmDoorClose);
    TerminateData(Data::diAcDoorOverride);
    TerminateData(Data::diVaporMHeaterAlarm);
    TerminateData(Data::diVaporVHeaterAlarm);
    TerminateData(Data::diHFReady);
    TerminateData(Data::diHeartbeatFail);
    TerminateData(Data::diExhaustAlarm);
    TerminateData(Data::diFacInletVPrsULmt);
    TerminateData(Data::diAlcoholLeak);
    TerminateData(Data::diPrcCbVacuum);
    TerminateData(Data::diPrcCbDoorClose);
    TerminateData(Data::diAlcoholGasLeak);
    TerminateData(Data::diGasboxDoorClose);
    TerminateData(Data::diDoorOverride);
    TerminateData(Data::diInterlockReset);
    TerminateData(Data::diHFLeak);
    TerminateData(Data::diThrottleValveOpen);
    TerminateData(Data::diHWInterlock);
    TerminateData(Data::diAlcTkLow);
    TerminateData(Data::diAlcTkHigh);
    TerminateData(Data::diAlcTkHighHigh);
    TerminateData(Data::diAlcTkOverfill);
    TerminateData(Data::diVPumpWarning);
    TerminateData(Data::diVPumpAlarm);

    TerminateData(Data::diPrcCbDoorOpen);
    TerminateData(Data::diWaferPickUp);
    TerminateData(Data::diWaferPickDown);
    TerminateData(Data::diWaferClamp);
    TerminateData(Data::diWaferUnclamp);
    TerminateData(Data::diArmInPos);
    TerminateData(Data::diArmOutPos);
    TerminateData(Data::diPrcCbLidLeftOpen);
    TerminateData(Data::diPrcCbLidLeftClose);
    TerminateData(Data::diPrcCbLidRightOpen);
    TerminateData(Data::diPrcCbLidRightClose);
    TerminateData(Data::diCbLeftDoorClose);
    TerminateData(Data::diCbRightDoorClose);

//DO
    TerminateData(Data::aoRedLight);
    TerminateData(Data::aoYellowLight);
    TerminateData(Data::aoGreenLight);
    TerminateData(Data::aoBlueLight);
    TerminateData(Data::aoBuzzer);
    TerminateData(Data::doHeartbeat);
    TerminateData(Data::doEnableVPump);
    TerminateData(Data::doHFRequest);
    TerminateData(Data::doExpCbVacValve);
    TerminateData(Data::doExpCbVapVacValve);
    TerminateData(Data::doAlcMFCBypassValve1);


    TerminateData(Data::flag);

	m_all_data.clear();
}

std::string SystemDataPool::ToJson(boost::function<bool (BaseSystemData*)> f)
{
	using namespace boost::property_tree;
	ptree array;
	BaseSystemData* data_ptr = nullptr;
	for(std::map<int, BaseSystemData*>::value_type& v : m_all_data)
	{
		data_ptr = v.second;
		if(data_ptr && (!f || f(data_ptr)))
			data_ptr->Serialize(array);
	}
	ptree pt;
	pt.add_child("systemdata", array);

	std::stringstream ss;
	json_parser::write_json(ss, pt);

	return ss.str();
}
