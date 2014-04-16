/*
 * Data.h
 *
 *  Created on: 2014Äê3ÔÂ5ÈÕ
 *      Author: acm
 */

#ifndef DATA_H_
#define DATA_H_

#include "SystemData.h"

namespace Data
{
extern SystemData<unsigned> diAlcPrsULmt;
extern SystemData<unsigned> diAlcPrsLLmt;
extern SystemData<unsigned> diAlcTkPrsULmt;
extern SystemData<unsigned> diAlcTkPrsLLmt;
extern SystemData<unsigned> diHFSplPrsULmt;
extern SystemData<unsigned> diHFSplPrsLLmt;
extern SystemData<unsigned> diN2PgHFPrsULmt;
extern SystemData<unsigned> diN2PgHFPrsLLmt;
extern SystemData<unsigned> diN2PgAlcTkPrsULmt;
extern SystemData<unsigned> diN2PgAlcTkPrsLLmt;
extern SystemData<unsigned> diN2PgExpCbPrsULmt;
extern SystemData<unsigned> diN2PgExpCbPrsLLmt;
extern SystemData<unsigned> diN2SplVPumpPrsULmt;
extern SystemData<unsigned> diN2SplVPumpPrsLLmt;
extern SystemData<unsigned> diN2PgPrcCbPrsULmt;
extern SystemData<unsigned> diN2PgPrcCbPrsLLmt;
extern SystemData<unsigned> diN2FacSplPrsULmt;
extern SystemData<unsigned> diN2FacSplPrsLLmt;
extern SystemData<unsigned> diN2PgVapPrsULmt;
extern SystemData<unsigned> diN2PgVapPrsLLmt;
extern SystemData<unsigned> diCDAInletAlarm;
extern SystemData<unsigned> diFacVPrsSwtLLmt;
extern SystemData<unsigned> diExpCbVPrsSwtULmt;
extern SystemData<unsigned> diExpCbVPrsSwtLLmt;
extern SystemData<unsigned> diIODoorClose;
extern SystemData<unsigned> diPCDoorClose;
extern SystemData<unsigned> diPneuDoorClose;
extern SystemData<unsigned> diAcFrmDoorClose;
extern SystemData<unsigned> diAcDoorOverride;
extern SystemData<unsigned> diVaporMHeaterAlarm;
extern SystemData<unsigned> diVaporVHeaterAlarm;
extern SystemData<unsigned> diHFReady;
extern SystemData<unsigned> diHeartbeatFail;
extern SystemData<unsigned> diExhaustAlarm;
extern SystemData<unsigned> diFacInletVPrsULmt;
extern SystemData<unsigned> diAlcoholLeak;
extern SystemData<unsigned> diPrcCbVacuum;
extern SystemData<unsigned> diPrcCbDoorClose;
extern SystemData<unsigned> diAlcoholGasLeak;
extern SystemData<unsigned> diGasboxDoorClose;
extern SystemData<unsigned> diDoorOverride;
extern SystemData<unsigned> diInterlockReset;
extern SystemData<unsigned> diHFLeak;
extern SystemData<unsigned> diThrottleValveOpen;
extern SystemData<unsigned> diHWInterlock;
extern SystemData<unsigned> diAlcTkLow;
extern SystemData<unsigned> diAlcTkHigh;
extern SystemData<unsigned> diAlcTkHighHigh;
extern SystemData<unsigned> diAlcTkOverfill;
extern SystemData<unsigned> diVPumpWarning;
extern SystemData<unsigned> diVPumpAlarm;

extern SystemData<unsigned> diPrcCbDoorOpen;
extern SystemData<unsigned> diWaferPickUp;
extern SystemData<unsigned> diWaferPickDown;
extern SystemData<unsigned> diWaferClamp;
extern SystemData<unsigned> diWaferUnclamp;
extern SystemData<unsigned> diArmInPos;
extern SystemData<unsigned> diArmOutPos;
extern SystemData<unsigned> diPrcCbLidLeftOpen;
extern SystemData<unsigned> diPrcCbLidLeftClose;
extern SystemData<unsigned> diPrcCbLidRightOpen;
extern SystemData<unsigned> diPrcCbLidRightClose;
extern SystemData<unsigned> diCbLeftDoorClose;
extern SystemData<unsigned> diCbRightDoorClose;

//DO
extern SystemData<unsigned> aoRedLight;
extern SystemData<unsigned> aoYellowLight;
extern SystemData<unsigned> aoGreenLight;
extern SystemData<unsigned> aoBlueLight;
extern SystemData<unsigned> aoBuzzer;
extern SystemData<unsigned> doHeartbeat;
extern SystemData<unsigned> doEnableVPump;
extern SystemData<unsigned> doHFRequest;
extern SystemData<unsigned> doExpCbVacValve;
extern SystemData<unsigned> doExpCbVapVacValve;
extern SystemData<unsigned> doAlcMFCBypassValve1;

//user defined
extern SystemData<unsigned> flag;

};

#endif /* DATA_H_ */
