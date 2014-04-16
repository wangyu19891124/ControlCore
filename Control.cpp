#include <fstream>

#include "EventLog.h"
#include "DeviceManager.h"
#include "SystemDataPool.h"
#include "WaferManager.h"
#include "Worker.h"

extern "C" void Initialize()
{
	LogFile::Instance().Initialize();
	Database::Instance().Initialize();
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
	Database::Instance().Terminate();
	LogFile::Instance().Terminate();
}

extern "C" void FetchParametersByIDRange(int from, int to, char** json)
{

}

extern "C" void FetchParametersByIDs(int* id_array, unsigned num, char** json)
{

}

extern "C" void FetchParametersByPath(const char* path, char** json)
{

}

extern "C" void FetchSystemDataByIDRange(int from, int to, bool only_changed, char** json)
{

}

extern "C" void FetchSystemDataByIDs(int* id_array, unsigned num, bool only_changed, char** json)
{

}

extern "C" void FetchParametersByPath(const char* path, bool only_changed, char** json)
{

}

extern "C" void FetchRecentEventLog(char** json)
{

}

extern "C" void Invoke(int unit, int cmd, unsigned param1, unsigned param2)
{

}
