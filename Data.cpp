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
SystemData<unsigned> diCDAInletAlarm(21, "diCDAInletAlarm", "DI", 0, 1, 0, 0, 0, 20, 0, 1, false,"",ConvertNot<unsigned int>);
SystemData<unsigned> diFacVPrsSwtLLmt(22, "diFacVPrsSwtLLmt", "DI", 0, 1, 0, 0, 0, 21, 0, 1, false);
SystemData<unsigned> diExpCbVPrsSwtULmt(23, "diExpCbVPrsSwtULmt", "DI", 0, 1, 0, 0, 0, 22, 0, 1, false);
SystemData<unsigned> diExpCbVPrsSwtLLmt(24, "diExpCbVPrsSwtLLmt", "DI", 0, 1, 0, 0, 0, 23, 0, 1, false);
SystemData<unsigned> diIODoorClose(25, "diIODoorClose", "DI", 0, 1, 0, 0, 0, 24, 0, 1, false);
SystemData<unsigned> diPCDoorClose(26, "diPCDoorClose", "DI", 0, 1, 0, 0, 0, 25, 0, 1, false);
SystemData<unsigned> diPneuDoorClose(27, "diPneuDoorClose", "DI", 0, 1, 0, 0, 0, 26, 0, 1, false);
SystemData<unsigned> diAcFrmDoorClose(28, "diAcFrmDoorClose", "DI", 0, 1, 0, 0, 0, 27, 0, 1, false);
SystemData<unsigned> diAcDoorOverride(29, "diAcDoorOverride", "DI", 0, 1, 0, 0, 0, 28, 0, 1, false);
SystemData<unsigned> diVaporMHeaterAlarm(30, "diVaporMHeaterAlarm", "DI", 0, 1, 0, 0, 0, 29, 0, 1, false,"",ConvertNot<unsigned int>);
SystemData<unsigned> diVaporVHeaterAlarm(31, "diVaporVHeaterAlarm", "DI", 0, 1, 0, 0, 0, 30, 0, 1, false,"",ConvertNot<unsigned int>);
SystemData<unsigned> diHFReady(32, "diHFReady", "DI", 0, 1, 0, 0, 0, 31, 0, 1, false);
SystemData<unsigned> diHeartbeatFail(33, "diHeartbeatFail", "DI", 0, 1, 0, 0, 0, 32, 0, 1, false,"",ConvertNot<unsigned int>);
SystemData<unsigned> diExhaustAlarm(34, "diExhaustAlarm", "DI", 0, 1, 0, 0, 0, 33, 0, 1, false,"",ConvertNot<unsigned int>);
SystemData<unsigned> diFacInletVPrsULmt(35, "diFacInletVPrsULmt", "DI", 0, 1, 0, 0, 0, 34, 0, 1, false,"",ConvertNot<unsigned int>);
SystemData<unsigned> diAlcoholLeak(36, "diAlcoholLeak", "DI", 0, 1, 0, 0, 0, 35, 0, 1, false,"",ConvertNot<unsigned int>);
SystemData<unsigned> diPrcCbVacuum(37, "diPrcCbVacuum", "DI", 0, 1, 0, 0, 0, 36, 0, 1, false,"",ConvertNot<unsigned int>);
SystemData<unsigned> diPrcCbDoorClose(38, "diPrcCbDoorClose", "DI", 0, 1, 0, 0, 0, 37, 0, 1, false);
SystemData<unsigned> diAlcoholGasLeak(39, "diAlcoholGasLeak", "DI", 0, 1, 0, 0, 0, 38, 0, 1, false,"",ConvertNot<unsigned int>);
SystemData<unsigned> diGasboxDoorClose(40, "diGasboxDoorClose", "DI", 0, 1, 0, 0, 0, 39, 0, 1, false,"",ConvertNot<unsigned int>);
SystemData<unsigned> diDoorOverride(41, "diDoorOverride", "DI", 0, 1, 0, 0, 0, 40, 0, 1, false);
SystemData<unsigned> diInterlockReset(42, "diInterlockReset", "DI", 0, 1, 0, 0, 0, 41, 0, 1, false);
SystemData<unsigned> diHFLeak(43, "diHFLeak", "DI", 0, 1, 0, 0, 0, 42, 0, 1, false,"",ConvertNot<unsigned int>);
SystemData<unsigned> diThrottleValveOpen(44, "diThrottleValveOpen", "DI", 0, 1, 0, 0, 0, 43, 0, 1, false);
SystemData<unsigned> diHWInterlock(45, "diHWInterlock", "DI", 0, 1, 0, 0, 0, 44, 0, 1, false);
SystemData<unsigned> diAlcTkLow(46, "diAlcTkLow", "DI", 0, 1, 0, 0, 0, 45, 0, 1, false);
SystemData<unsigned> diAlcTkHigh(47, "diAlcTkHigh", "DI", 0, 1, 0, 0, 0, 46, 0, 1, false);
SystemData<unsigned> diAlcTkHighHigh(48, "diAlcTkHighHigh", "DI", 0, 1, 0, 0, 0, 47, 0, 1, false);
SystemData<unsigned> diAlcTkOverfill(49, "diAlcTkOverfill", "DI", 0, 1, 0, 0, 0, 48, 0, 1, false);
SystemData<unsigned> diVPumpWarning(50, "diVPumpWarning", "DI", 0, 1, 0, 0, 0, 49, 0, 1, false,"",ConvertNot<unsigned int>);
SystemData<unsigned> diVPumpAlarm(51, "diVPumpAlarm", "DI", 0, 1, 0, 0, 0, 50, 0, 1, false,"",ConvertNot<unsigned int>);
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
SystemData<unsigned> diCbHFConAlarm(78, "diCbHFConAlarm","DI",0,1,0,0,0,77,0,1,false,"",ConvertNot<unsigned int>);
SystemData<unsigned> diProcCbBodyHeater(79, "diProcCbBodyHeater","DI/Heater",0,1,0,0,4,0,0,1,false);
SystemData<unsigned> diProcCbLidHeater(80, "diProcCbLidHeater","DI/Heater",0,1,0,0,4,1,0,1,false);
SystemData<unsigned> diProcCbChuckHeater(81, "diProcCbChuckHeater","DI/Heater",0,1,0,0,4,2,0,1,false);
SystemData<unsigned> diCbA1MotorAlarm(82,"diCbA1MotorAlarm","DI/Motion",0,1,0,0,5,0,0,1,false);
SystemData<unsigned> diCbA1MotorCWLmit(83,"diCbA1MotorCWLmit","DI/Motion",0,1,0,0,5,1,0,1,false,"",ConvertNot<unsigned int>);
SystemData<unsigned> diCbA1MotorCCWLmit(84,"diCbA1MotorCCWLmit","DI/Motion",0,1,0,0,5,2,0,1,false,"",ConvertNot<unsigned int>);
SystemData<unsigned> diCbMotorHome(85,"diCbMotorHome","DI/Motion",0,1,0,0,5,3,0,1,false);


//DO
SystemData<unsigned> doRedLight(1000,"doRedLight","DO",0,1,0,0,1,0,0,1,true);
SystemData<unsigned> doRedFlash(1001,"doRedFlash","DO",0,1,0,0,1,1,0,1,true);
SystemData<unsigned> doYellowLight(1002,"doYellowLight","DO",0,1,0,0,1,2,0,1,true);
SystemData<unsigned> doYellowFlash(1003,"doYellowFlash","DO",0,1,0,0,1,3,0,1,true);
SystemData<unsigned> doGreenLight(1004,"doGreenLight","DO",0,1,0,0,1,4,0,1,true);
SystemData<unsigned> doGreenFlash(1005,"doGreenFlash","DO",0,1,0,0,1,5,0,1,true);
SystemData<unsigned> doBlueLight(1006,"doBlueLight","DO",0,1,0,0,1,6,0,1,true);
SystemData<unsigned> doBlueFlash(1007,"doBlueFlash","DO",0,1,0,0,1,7,0,1,true);
SystemData<unsigned> doBuzzerWarn(1008,"doBuzzerWarn","DO",0,1,0,0,1,8,0,1,true);
SystemData<unsigned> doBuzzerAlarm(1009,"doBuzzerAlarm","DO",0,1,0,0,1,9,0,1,true);
SystemData<unsigned> doHeartBeat(1010,"doHeartBeat","DO",0,1,0,0,1,10,0,1,true);
SystemData<unsigned> doEnableVPump(1011,"doEnableVPump","DO",0,1,0,0,1,11,0,1,true);
SystemData<unsigned> doHFRequest(1012,"doHFRequest","DO",0,1,0,0,1,12,0,1,true);
SystemData<unsigned> doN2PurgeGasValve(1013,"doN2PurgeGasValve","DO",0,1,0,0,1,16,0,1,true);
SystemData<unsigned> doExpCbVacValve(1014,"doExpCbVacValve","DO",0,1,0,0,1,18,0,1,true);
SystemData<unsigned> doExpCbVapVacValve(1015,"doExpCbVapVacValve","DO",0,1,0,0,1,19,0,1,true);
SystemData<unsigned> doAlcMFCBypassVal1(1016,"doAlcMFCBypassVal1","DO",0,1,0,0,1,21,0,1,true);
SystemData<unsigned> doAlcMFCBypassVal2(1017,"doAlcMFCBypassVal2","DO",0,1,0,0,1,22,0,1,true);
SystemData<unsigned> doAlcMFCBypassVal3(1018,"doAlcMFCBypassVal3","DO",0,1,0,0,1,23,0,1,true);
SystemData<unsigned> doVapSupplyN2Valve(1019,"doVapSupplyN2Valve","DO",0,1,0,0,1,24,0,1,true);
SystemData<unsigned> doVapBypassValve(1020,"doVapBypassValve","DO",0,1,0,0,1,25,0,1,true);
SystemData<unsigned> doA2cMFCBypassVal1(1021,"doA2cMFCBypassVal1","DO",0,1,0,0,1,26,0,1,true);
SystemData<unsigned> doA2cMFCBypassVal2(1022,"doA2cMFCBypassVal2","DO",0,1,0,0,1,27,0,1,true);
SystemData<unsigned> doA2cMFCBypassVal3(1023,"doA2cMFCBypassVal3","DO",0,1,0,0,1,28,0,1,true);
SystemData<unsigned> doA3cMFCBypassVal1(1024,"doA3cMFCBypassVal1","DO",0,1,0,0,1,29,0,1,true);
SystemData<unsigned> doA3cMFCBypassVal2(1025,"doA3cMFCBypassVal2","DO",0,1,0,0,1,30,0,1,true);
SystemData<unsigned> doVaVapValve(1026,"doVaVapValve","DO",0,1,0,0,1,32,0,1,true);
SystemData<unsigned> doVaHFValve(1027,"doVaHFValve","DO",0,1,0,0,1,33,0,1,true);
SystemData<unsigned> doVaSupplyIPAValve(1028,"doVaSupplyIPAValve","DO",0,1,0,0,1,34,0,1,true);
SystemData<unsigned> doExpCbVacIPASupply(1029,"doExpCbVacIPASupply","DO",0,1,0,0,1,35,0,1,true);
SystemData<unsigned> doAlcTankOpen(1030,"doAlcTankOpen","DO",0,1,0,0,1,36,0,1,true);
SystemData<unsigned> doPurgeAlcTank(1031,"doPurgeAlcTank","DO",0,1,0,0,1,37,0,1,true);
SystemData<unsigned> doExpCbHFInletVal(1032,"doExpCbHFInletVal","DO",0,1,0,0,1,38,0,1,true);
SystemData<unsigned> doHFFacSupplyVal(1033,"doHFFacSupplyVal","DO",0,1,0,0,1,39,0,1,true);
SystemData<unsigned> doN2PurgeHFVal(1034,"doN2PurgeHFVal","DO",0,1,0,0,1,40,0,1,true);
SystemData<unsigned> doExpCbSupplyCbVal(1035,"doExpCbSupplyCbVal","DO",0,1,0,0,1,41,0,1,true);
SystemData<unsigned> doN2SupplyVacVal(1036,"doN2SupplyVacVal","DO",0,1,0,0,1,48,0,1,true);
SystemData<unsigned> doN2SupplyProcVal(1037,"doN2SupplyProcVal","DO",0,1,0,0,1,49,0,1,true);
SystemData<unsigned> doA4cMFCBypassVal1(1038,"doA4cMFCBypassVal1","DO",0,1,0,0,1,50,0,1,true);
SystemData<unsigned> doA4cMFCBypassVal2(1039,"doA4cMFCBypassVal2","DO",0,1,0,0,1,51,0,1,true);
SystemData<unsigned> doPinUpVal(1040,"doPinUpVal","DO",0,1,0,0,1,52,0,1,true);
SystemData<unsigned> doVacFastProcCbVal(1041,"doVacFastProcCbVal","DO",0,1,0,0,1,56,0,1,true);
SystemData<unsigned> doVacSlowProcCbVal(1042,"doVacSlowProcCbVal","DO",0,1,0,0,1,57,0,1,true);
SystemData<unsigned> doPinDownVal(1042,"doPinDownVal","DO",0,1,0,0,1,63,0,1,true);
SystemData<unsigned> doCbGateVal(1043,"doCbGateVal","DO",0,1,0,0,1,71,0,1,true);
SystemData<unsigned> doHeartbeatIntlk(1044,"doHeartbeatIntlk","DO",0,1,0,0,1,80,0,1,true,"",ConvertNot<unsigned int>);
SystemData<unsigned> doMainVacIntlk(1045,"doMainVacIntlk","DO",0,1,0,0,1,81,0,1,true,"",ConvertNot<unsigned int>);
SystemData<unsigned> doGeneralIntlk(1046,"doGeneralIntlk","DO",0,1,0,0,1,82,0,1,true,"",ConvertNot<unsigned int>);
SystemData<unsigned> doCHEM1ReqIntlk(1047,"doCHEM1ReqIntlk","DO",0,1,0,0,1,83,0,1,true,"",ConvertNot<unsigned int>);
SystemData<unsigned> doResetLED(1049,"doResetLED","DO",0,1,0,0,1,84,0,1,true);
SystemData<unsigned> doHWIntlk(1050,"doHWIntlk","DO",0,1,0,0,1,85,0,1,true,"",ConvertNot<unsigned int>);
SystemData<unsigned> doN2PurgeGasIntlk(1051,"doN2PurgeGasIntlk","DO",0,1,0,0,1,86,0,1,true,"",ConvertNot<unsigned int>);
SystemData<unsigned> doMotionIntlk(1052,"doMotionIntlk","DO",0,1,0,0,1,87,0,1,true,"",ConvertNot<unsigned int>);
SystemData<unsigned> doProcCbBodyHeatEnable(1053,"doProcCbBodyHeatEnable","DO",0,1,0,0,1,88,0,1,true);
SystemData<unsigned> doProcCbLidHeatEnable(1054,"doProcCbLidHeatEnable","DO",0,1,0,0,1,89,0,1,true);
SystemData<unsigned> doCbCkHeatEnable(1055,"doCbCkHeatEnable","DO",0,1,0,0,1,90,0,1,true);
SystemData<unsigned> doCbMotorServoOn(1056,"doCbMotorServoOn","DO",0,1,0,0,5,0,0,1,true);


//AI
SystemData<unsigned> aiFacVacPrs(2000,"aiFacVacPrs","AI",0,0x101,0,0,2,0,0,16,false,"KPA");
SystemData<unsigned> aiExpCbVacPrs(2001,"aiExpCbVacPrs","AI",0,0x101,0,0,2,1,0,16,false,"KPA");



SystemData<unsigned> aoRedLight(1000, "aoRedLight", "DO", 0, 0x101, 0, 0, 1, 0, 0, 16, true);
SystemData<unsigned> aoYellowLight(1001, "aoYellowLight", "DO", 0, 0x101, 0, 0, 1, 2, 0, 16, true);
SystemData<unsigned> aoGreenLight(1002, "aoGreenLight", "DO", 0, 0x101, 0, 0, 1, 4, 0, 16, true);


//user defined
SystemData<unsigned> flag(100011, "flag", "UserDefine", 0, 1000);
SystemData<std::string> RecipeName(100013, "RecipeName", "UserDefine");

}
