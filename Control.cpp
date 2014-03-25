#include <fstream>

#include "EventLog.h"
#include "DeviceManager.h"
#include "SystemDataPool.h"
#include "WaferManager.h"
#include "Worker.h"

extern "C" void Initialize()
{
	EventLogger::Instance().Initialize();
	Worker::Instance().Initialize();
	DeviceManager::Instance().Initialize();
	SystemDataPool::Instance().Initialize();
	WaferManager::Instance().Initialize();
}

extern "C" void Terminate()
{
	WaferManager::Instance().Terminate();
	SystemDataPool::Instance().Terminate();
	DeviceManager::Instance().Terminate();
	Worker::Instance().Terminate();
	EventLogger::Instance().Terminate();
}

