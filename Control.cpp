#include <fstream>

#include "EventLog.h"
#include "DeviceManager.h"
#include "SystemDataPool.h"
#include "WaferManager.h"
#include "Worker.h"
#include "LogFile.h"
#include "Database.h"
#include "SystemParameter.h"
#include "Interlock.h"

extern "C" void Initialize()
{
	LogFile::Instance().Initialize();
	Database::Instance().Initialize();
	EventLogger::Instance().Initialize();
	Worker::Instance().Initialize();
	DeviceManager::Instance().Initialize();
	SystemDataPool::Instance().Initialize();
	Interlock::Instance().Initialize();
	WaferManager::Instance().Initialize();
}

extern "C" void Terminate()
{
	WaferManager::Instance().Terminate();
	Interlock::Instance().Terminate();
	SystemDataPool::Instance().Terminate();
	DeviceManager::Instance().Terminate();
	Worker::Instance().Terminate();
	EventLogger::Instance().Terminate();
	Database::Instance().Terminate();
	LogFile::Instance().Terminate();
}

void alloc_and_copy_string(char** json, const std::string& json_string)
{
	size_t size = json_string.size()+1;
	*json = new char[size];
	std::copy(json_string.begin(), json_string.end(), *json);
	*(*json+size-1) = 0;
}

extern "C" void FetchParametersByIDRange(int from, int to, char** json)
{
	std::string json_string;
	json_string = SystemParameter::Instance().GetJsonData([from, to](ParameterItemBase* p){return p->IsInRange(from, to);});
	alloc_and_copy_string(json, json_string);
}

extern "C" void FetchParametersByIDs(int* id_array, unsigned num, char** json)
{
	std::set<int> id_set;
	for(unsigned i=0; i<num; i++)
	{
		id_set.insert(*(id_array+i));
	}
	std::string json_string;
	json_string = SystemParameter::Instance().GetJsonData([&id_set](ParameterItemBase* p){return p->IsInSet(id_set);});
	alloc_and_copy_string(json, json_string);
}

extern "C" void FetchParametersByPath(const char* path, char** json)
{
	std::string json_string;
	json_string = SystemParameter::Instance().GetJsonData([path](ParameterItemBase* p){return p->IsChild(path);});
	alloc_and_copy_string(json, json_string);
}

extern "C" void FetchSystemDataByIDRange(int from, int to, bool only_changed, char** json)
{
	std::string json_string;
	json_string = SystemDataPool::Instance().GetJsonData(
			[from, to, only_changed](BaseSystemData* p)
			{
				return p->IsInRange(from, to)
						&& (!only_changed || (only_changed && p->HasChanged()));
			});
	alloc_and_copy_string(json, json_string);
}

extern "C" void FetchSystemDataByIDs(int* id_array, unsigned num, bool only_changed, char** json)
{
	std::set<int> id_set;
	for(unsigned i=0; i<num; i++)
	{
		id_set.insert(*(id_array+i));
	}

	std::string json_string;
	json_string = SystemDataPool::Instance().GetJsonData(
			[&id_set, only_changed](BaseSystemData* p)
			{
				return p->IsInSet(id_set)
						&& (!only_changed || (only_changed && p->HasChanged()));
			});
	alloc_and_copy_string(json, json_string);
}

extern "C" void FetchSystemDataByPath(const char* path, bool only_changed, char** json)
{
	std::string json_string;
	json_string = SystemDataPool::Instance().GetJsonData(
			[path, only_changed](BaseSystemData* p)
			{
				return p->IsChild(path)
						&& (!only_changed || (only_changed && p->HasChanged()));
			});
	alloc_and_copy_string(json, json_string);
}

extern "C" void FetchRecentEventLog(char** json)
{
	std::string json_string;
	json_string = EventLogger::Instance().FetchLogs();
	alloc_and_copy_string(json, json_string);
}

extern "C" void Invoke(int unit, int cmd, unsigned param1, unsigned param2)
{

}
