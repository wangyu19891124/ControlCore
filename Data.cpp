/*
 * Data.cpp
 *
 *  Created on: 2014Äê3ÔÂ5ÈÕ
 *      Author: acm
 */

#include "SystemData.h"

namespace Data
{

//DI
SystemData<unsigned> diAlcPrsULmt(1, "diAlcPrsULmt", "DI", 0, 1, 0, 0, 0, 0, 0, 1, false);
SystemData<unsigned> diAlcPrsLLmt(2, "diAlcPrsLLmt", "DI", 0, 1, 0, 0, 0, 1, 0, 1, false);
SystemData<unsigned> diAlcTkPrsULmt(3, "diAlcTkPrsULmt", "DI", 0, 1, 0, 0, 0, 2, 0, 1, false);
SystemData<unsigned> diAlcTkPrsLLmt(4, "diAlcTkPrsLLmt", "DI", 0, 1, 0, 0, 0, 3, 0, 1, false);
SystemData<unsigned> diHFSplPrsULmt(5, "diHFSplPrsULmt", "DI", 0, 1, 0, 0, 0, 4, 0, 1, false);
SystemData<unsigned> diHFSplPrsLLmt(6, "diHFSplPrsLLmt", "DI", 0, 1, 0, 0, 0, 5, 0, 1, false);
SystemData<unsigned> diN2PgHFPrsULmt(7, "diN2PgHFPrsULmt", "DI", 0, 1, 0, 0, 0, 6, 0, 1, false);
SystemData<unsigned> diN2PgHFPrsLLmt(8, "diN2PgHFPrsLLmt", "DI", 0, 1, 0, 0, 0, 7, 0, 1, false);
SystemData<unsigned> diN2PgAlcTkPrsULmt(9, "diN2PgAlcTkPrsULmt", "DI", 0, 1, 0, 0, 0, 8, 0, 1, false);
SystemData<unsigned> diN2PgAlcTkPrsLLmt(10, "diN2PgAlcTkPrsLLmt", "DI", 0, 1, 0, 0, 0, 9, 0, 1, false);
SystemData<unsigned> diN2PgExpCbPrsULmt(11, "diN2PgExpCbPrsULmt", "DI", 0, 1, 0, 0, 0, 10, 0, 1, false);
SystemData<unsigned> diN2PgExpCbPrsLLmt(12, "diN2PgExpCbPrsLLmt", "DI", 0, 1, 0, 0, 0, 11, 0, 1, false);
SystemData<unsigned> diN2SplVPumpPrsULmt(13, "diN2SplVPumpPrsULmt", "DI", 0, 1, 0, 0, 0, 12, 0, 1, false);
SystemData<unsigned> diN2SplVPumpPrsLLmt(14, "diN2SplVPumpPrsLLmt", "DI", 0, 1, 0, 0, 0, 13, 0, 1, false);
SystemData<unsigned> diN2PgPrcCbPrsULmt(15, "diN2PgPrcCbPrsULmt", "DI", 0, 1, 0, 0, 0, 14, 0, 1, false);
SystemData<unsigned> diN2PgPrcCbPrsLLmt(16, "diN2PgPrcCbPrsLLmt", "DI", 0, 1, 0, 0, 0, 15, 0, 1, false);
SystemData<unsigned> diN2FacSplPrsULmt(17, "diN2FacSplPrsULmt", "DI", 0, 1, 0, 0, 0, 16, 0, 1, false);
SystemData<unsigned> diN2FacSplPrsLLmt(18, "diN2FacSplPrsLLmt", "DI", 0, 1, 0, 0, 0, 17, 0, 1, false);
SystemData<unsigned> diN2PgVapPrsULmt(19, "diN2PgVapPrsULmt", "DI", 0, 1, 0, 0, 0, 18, 0, 1, false);
SystemData<unsigned> diN2PgVapPrsLLmt(20, "diN2PgVapPrsLLmt", "DI", 0, 1, 0, 0, 0, 19, 0, 1, false);
SystemData<unsigned> diCDAInletAlarm(21, "diCDAInletAlarm", "DI", 0, 1, 0, 0, 0, 20, 0, 1, false);
SystemData<unsigned> diFacVPrsSwtLLmt(22, "diFacVPrsSwtLLmt", "DI", 0, 1, 0, 0, 0, 21, 0, 1, false);
SystemData<unsigned> diExpCbVPrsSwtULmt(23, "diExpCbVPrsSwtULmt", "DI", 0, 1, 0, 0, 0, 22, 0, 1, false);
SystemData<unsigned> diExpCbVPrsSwtLLmt(24, "diExpCbVPrsSwtLLmt", "DI", 0, 1, 0, 0, 0, 23, 0, 1, false);
SystemData<unsigned> diIODoorClose(25, "diIODoorClose", "DI", 0, 1, 0, 0, 0, 24, 0, 1, false);
SystemData<unsigned> diPCDoorClose(26, "diPCDoorClose", "DI", 0, 1, 0, 0, 0, 25, 0, 1, false);
SystemData<unsigned> diPneuDoorClose(27, "diPneuDoorClose", "DI", 0, 1, 0, 0, 0, 26, 0, 1, false);
SystemData<unsigned> diAcFrmDoorClose(28, "diAcFrmDoorClose", "DI", 0, 1, 0, 0, 0, 27, 0, 1, false);
SystemData<unsigned> diAcDoorOverride(29, "diAcDoorOverride", "DI", 0, 1, 0, 0, 0, 28, 0, 1, false);
SystemData<unsigned> diVaporMHeaterAlarm(30, "diVaporMHeaterAlarm", "DI", 0, 1, 0, 0, 0, 29, 0, 1, false);
SystemData<unsigned> diVaporVHeaterAlarm(31, "diVaporVHeaterAlarm", "DI", 0, 1, 0, 0, 0, 30, 0, 1, false);
SystemData<unsigned> diHFReady(32, "diHFReady", "DI", 0, 1, 0, 0, 0, 31, 0, 1, false);
SystemData<unsigned> diHeartbeatFail(33, "diHeartbeatFail", "DI", 0, 1, 0, 0, 0, 32, 0, 1, false);
SystemData<unsigned> diExhaustAlarm(34, "diExhaustAlarm", "DI", 0, 1, 0, 0, 0, 33, 0, 1, false);
SystemData<unsigned> diFacInletVPrsULmt(35, "diFacInletVPrsULmt", "DI", 0, 1, 0, 0, 0, 34, 0, 1, false);
SystemData<unsigned> diAlcoholLeak(36, "diAlcoholLeak", "DI", 0, 1, 0, 0, 0, 35, 0, 1, false);
SystemData<unsigned> diPrcCbVacuum(37, "diPrcCbVacuum", "DI", 0, 1, 0, 0, 0, 36, 0, 1, false);
SystemData<unsigned> diPrcCbDoorClose(38, "diPrcCbDoorClose", "DI", 0, 1, 0, 0, 0, 37, 0, 1, false);
SystemData<unsigned> diAlcoholGasLeak(39, "diAlcoholGasLeak", "DI", 0, 1, 0, 0, 0, 38, 0, 1, false);
SystemData<unsigned> diGasboxDoorClose(40, "diGasboxDoorClose", "DI", 0, 1, 0, 0, 0, 39, 0, 1, false);
SystemData<unsigned> diDoorOverride(41, "diDoorOverride", "DI", 0, 1, 0, 0, 0, 40, 0, 1, false);
SystemData<unsigned> diInterlockReset(42, "diInterlockReset", "DI", 0, 1, 0, 0, 0, 41, 0, 1, false);
SystemData<unsigned> diHFLeak(43, "diHFLeak", "DI", 0, 1, 0, 0, 0, 42, 0, 1, false);
SystemData<unsigned> diThrottleValveOpen(44, "diThrottleValveOpen", "DI", 0, 1, 0, 0, 0, 43, 0, 1, false);
SystemData<unsigned> diHWInterlock(45, "diHWInterlock", "DI", 0, 1, 0, 0, 0, 44, 0, 1, false);
SystemData<unsigned> diAlcTkLow(46, "diAlcTkLow", "DI", 0, 1, 0, 0, 0, 45, 0, 1, false);
SystemData<unsigned> diAlcTkHigh(47, "diAlcTkHigh", "DI", 0, 1, 0, 0, 0, 46, 0, 1, false);
SystemData<unsigned> diAlcTkHighHigh(48, "diAlcTkHighHigh", "DI", 0, 1, 0, 0, 0, 47, 0, 1, false);
SystemData<unsigned> diAlcTkOverfill(49, "diAlcTkOverfill", "DI", 0, 1, 0, 0, 0, 48, 0, 1, false);
SystemData<unsigned> diVPumpWarning(50, "diVPumpWarning", "DI", 0, 1, 0, 0, 0, 49, 0, 1, false);
SystemData<unsigned> diVPumpAlarm(51, "diVPumpAlarm", "DI", 0, 1, 0, 0, 0, 50, 0, 1, false);

SystemData<unsigned> diPrcCbDoorOpen(60, "diPrcCbDoorOpen", "DI", 0, 1, 0, 0, 0, 59, 0, 1, false);
SystemData<unsigned> diWaferPickUp(61, "diWaferPickUp", "DI", 0, 1, 0, 0, 0, 60, 0, 1, false);
SystemData<unsigned> diWaferPickDown(62, "diWaferPickDown", "DI", 0, 1, 0, 0, 0, 61, 0, 1, false);
SystemData<unsigned> diWaferClamp(63, "diWaferClamp", "DI", 0, 1, 0, 0, 0, 62, 0, 1, false);
SystemData<unsigned> diWaferUnclamp(64, "diWaferUnclamp", "DI", 0, 1, 0, 0, 0, 63, 0, 1, false);
SystemData<unsigned> diArmInPos(65, "diArmInPos", "DI", 0, 1, 0, 0, 0, 64, 0, 1, false);
SystemData<unsigned> diArmOutPos(66, "diArmOutPos", "DI", 0, 1, 0, 0, 0, 65, 0, 1, false);
SystemData<unsigned> diPrcCbLidLeftOpen(67, "diPrcCbLidLeftOpen", "DI", 0, 1, 0, 0, 0, 66, 0, 1, false);
SystemData<unsigned> diPrcCbLidLeftClose(68, "diPrcCbLidLeftClose", "DI", 0, 1, 0, 0, 0, 67, 0, 1, false);
SystemData<unsigned> diPrcCbLidRightOpen(69, "diPrcCbLidRightOpen", "DI", 0, 1, 0, 0, 0, 68, 0, 1, false);
SystemData<unsigned> diPrcCbLidRightClose(70, "diPrcCbLidRightClose", "DI", 0, 1, 0, 0, 0, 69, 0, 1, false);
SystemData<unsigned> diCbLeftDoorClose(76, "diCbLeftDoorClose", "DI", 0, 1, 0, 0, 0, 75, 0, 1, false);
SystemData<unsigned> diCbRightDoorClose(77, "diCbRightDoorClose", "DI", 0, 1, 0, 0, 0, 76, 0, 1, false);

//DO
SystemData<unsigned> aoRedLight(1000, "aoRedLight", "DO", 0, 0x101, 0, 0, 1, 0, 0, 16, true);
SystemData<unsigned> aoYellowLight(1001, "aoYellowLight", "DO", 0, 0x101, 0, 0, 1, 2, 0, 16, true);
SystemData<unsigned> aoGreenLight(1002, "aoGreenLight", "DO", 0, 0x101, 0, 0, 1, 4, 0, 16, true);
SystemData<unsigned> aoBlueLight(1003, "aoBlueLight", "DO", 0, 0x101, 0, 0, 1, 6, 0, 16, true);
SystemData<unsigned> aoBuzzer(1004, "aoBuzzer", "DO", 0, 0x101, 0, 0, 1, 8, 0, 16, true);
SystemData<unsigned> doHeartbeat(1005, "doHeartbeat", "DO", 0, 1, 0, 0, 1, 10, 0, 1, true);
SystemData<unsigned> doEnableVPump(1006, "doEnableVPump", "DO", 0, 1, 0, 0, 1, 11, 0, 1, true);
SystemData<unsigned> doHFRequest(1007, "doHFRequest", "DO", 0, 1, 0, 0, 1, 12, 0, 1, true);
SystemData<unsigned> doExpCbVacValve(1013, "doExpCbVacValve", "DO", 0, 1, 0, 0, 1, 18, 0, 1, true);
SystemData<unsigned> doExpCbVapVacValve(1014, "doExpCbVapVacValve", "DO", 0, 1, 0, 0, 1, 19, 0, 1, true);
SystemData<unsigned> doAlcMFCBypassValve1(1016, "doAlcMFCBypassValve1", "DO", 0, 1, 0, 0, 1, 20, 0, 1, true);

//user defined
SystemData<unsigned> flag(100011, "flag", "UserDefine", 0, 1000);

}
