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
extern SystemData<unsigned> diProcCbBodyHeater;
extern SystemData<unsigned> diProcCbLidHeater;
extern SystemData<unsigned> diProcCbChuckHeater;

extern SystemData<unsigned> diCbA1MotorAlarm;
extern SystemData<unsigned> diCbA1MotorCWLmit;
extern SystemData<unsigned> diCbA1MotorCCWLmit;
extern SystemData<unsigned> diCbMotorHome;

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
extern SystemData<unsigned> diCbHFConAlarm;

//DO
extern SystemData<unsigned> doRedLight;
extern SystemData<unsigned> doRedFlash;
extern SystemData<unsigned> doYellowLight;
extern SystemData<unsigned> doYellowFlash;
extern SystemData<unsigned> doGreenLight;
extern SystemData<unsigned> doGreenFlash;
extern SystemData<unsigned> doBlueLight;
extern SystemData<unsigned> doBlueFlash;
extern SystemData<unsigned> doBuzzerWarn;
extern SystemData<unsigned> doBuzzerAlarm;
extern SystemData<unsigned> doHeartbeat;
extern SystemData<unsigned> doEnableVPump;
extern SystemData<unsigned> doHFRequest;
extern SystemData<unsigned> doN2PurgeGasValve;
extern SystemData<unsigned> doExpCbVacValve;
extern SystemData<unsigned> doExpCbVapVacValve;
extern SystemData<unsigned> doAlcMFCBypassVal1;
extern SystemData<unsigned> doA1cMFCBypassVal2;
extern SystemData<unsigned> doA1cMFCBypassVal3;
extern SystemData<unsigned> doVapSupplyN2Valve;
extern SystemData<unsigned> doVapBypassValve;
extern SystemData<unsigned> doA2cMFCBypassVal1;
extern SystemData<unsigned> doA2cMFCBypassVal2;
extern SystemData<unsigned> doA2cMFCBypassVal3;
extern SystemData<unsigned> doA3cMFCBypassVal1;
extern SystemData<unsigned> doA3cMFCBypassVal2;
extern SystemData<unsigned> doVaVapValve;
extern SystemData<unsigned> doVaHFValve;
extern SystemData<unsigned> doVaSupplyIPAValve;
extern SystemData<unsigned> doExpCbVacIPASupply;
extern SystemData<unsigned> doAlcTankOpen;
extern SystemData<unsigned> doPurgeAlcTank;
extern SystemData<unsigned> doExpCbHFInletVal;
extern SystemData<unsigned> doHFFacSupplyVal;
extern SystemData<unsigned> doN2PurgeHFVal;
extern SystemData<unsigned> doExpCbSupplyCbVal;
extern SystemData<unsigned> doN2SupplyVacVal;
extern SystemData<unsigned> doN2SupplyProcVal;
extern SystemData<unsigned> doA4cMFCBypassVal1;
extern SystemData<unsigned> doA4cMFCBypassVal2;
extern SystemData<unsigned> doPinUpVal;
extern SystemData<unsigned> doVacFastProcCbVal;
extern SystemData<unsigned> doVacSlowProcCbVal;
extern SystemData<unsigned> doPinDownVal;
extern SystemData<unsigned> doCbGateVal;
extern SystemData<unsigned> doHeartbeatIntlk;
extern SystemData<unsigned> doMainVacIntlk;
extern SystemData<unsigned> doGeneralIntlk;
extern SystemData<unsigned> doCHEM1ReqIntlk;
extern SystemData<unsigned> doResetLED;
extern SystemData<unsigned> doHWIntlk;
extern SystemData<unsigned> doN2PurgeGasIntlk;
extern SystemData<unsigned> doMotionIntlk;
extern SystemData<unsigned> doProcCbBodyHeatEnable;
extern SystemData<unsigned> doProcCbLidHeatEnable;
extern SystemData<unsigned> doCbCkHeatEnable;

extern SystemData<unsigned> doCbMotorServoOn;
extern SystemData<unsigned> doCbMotorAlarmRes;

//AI
extern SystemData<unsigned> aiFacVacPrs;
extern SystemData<unsigned> aiExpCbVacPrs;
extern SystemData<unsigned> aiAlcGasPrs;
extern SystemData<unsigned> aiAlcTankGasPrs;
extern SystemData<unsigned> aiHFSupplyPrs;
extern SystemData<unsigned> aiEthGasLeak;
extern SystemData<unsigned> aiGasHFConcen;
extern SystemData<unsigned> aiCbHFConcen;
//user defined
extern SystemData<unsigned> flag;
extern SystemData<std::string> RecipeName;

};

#endif /* DATA_H_ */
