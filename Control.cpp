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
#include "DataRecorder.h"

extern "C" void Initialize()
{
	LogFile::Instance().Initialize();
	Database::Instance().Initialize();
	EventLogger::Instance().Initialize();
	Worker::Instance().Initialize();
	DeviceManager::Instance().Initialize();
	SystemDataPool::Instance().Initialize();
	LogDebug("6");
	Interlock::Instance().Initialize();
	LogDebug("7");
	DataRecorder::Instance().Initialize();
	LogDebug("8");
	WaferManager::Instance().Initialize();
	LogDebug("9");
}

extern "C" void Terminate()
{
	WaferManager::Instance().Terminate();
	DataRecorder::Instance().Terminate();
	Interlock::Instance().Terminate();
	SystemDataPool::Instance().Terminate();
	DeviceManager::Instance().Terminate();
	Worker::Instance().Terminate();
	EventLogger::Instance().Terminate();
	Database::Instance().Terminate();
	LogFile::Instance().Terminate();
}

int copy_string(char* json, unsigned buffer_size, const std::string& json_string)
{
	size_t string_size = json_string.size();
	size_t size = std::min(string_size, buffer_size);
	std::copy(json_string.c_str(), json_string.c_str()+size, json);

	return size;
}

extern "C" int FetchParametersByIDRange(int from, int to, char* json, unsigned buffer_size)
{
	std::string json_string;
	json_string = SystemParameter::Instance().GetJsonData([from, to](ParameterItemBase* p){return p->IsInRange(from, to);});

	return copy_string(json, buffer_size, json_string);
}

extern "C" int FetchParametersByIDs(const int* id_array, unsigned num, char* json, unsigned buffer_size)
{
	std::set<int> id_set;
	for(unsigned i=0; i<num; i++)
	{
		id_set.insert(*(id_array+i));
	}
	std::string json_string;
	json_string = SystemParameter::Instance().GetJsonData([&id_set](ParameterItemBase* p){return p->IsInSet(id_set);});
	return copy_string(json, buffer_size, json_string);
}

extern "C" int FetchParametersByPath(const char* path, char* json, unsigned buffer_size)
{
	std::string json_string;
	json_string = SystemParameter::Instance().GetJsonData([path](ParameterItemBase* p){return p->IsChild(path);});
	return copy_string(json, buffer_size, json_string);
}

extern "C" void ModifyParameter(int id, const char* value)
{
	SystemParameter::Instance().SetData(id, value);
}

extern "C" int FetchSystemDataByIDRange(int from, int to, bool only_changed, char* json, unsigned buffer_size)
{
	std::string json_string;
	json_string = SystemDataPool::Instance().GetJsonData(
			[from, to, only_changed](BaseSystemData* p)
			{
				return p->IsInRange(from, to)
						&& (!only_changed || (only_changed && p->HasChanged()));
			});
	return copy_string(json, buffer_size, json_string);
}

extern "C" int FetchSystemDataByIDs(int* id_array, unsigned num, bool only_changed, char* json, unsigned buffer_size)
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
	return copy_string(json, buffer_size, json_string);
}

extern "C" int FetchSystemDataByPath(const char* path, bool only_changed, char* json, unsigned buffer_size)
{
	std::string json_string;
	json_string = SystemDataPool::Instance().GetJsonData(
			[path, only_changed](BaseSystemData* p)
			{
				return p->IsChild(path)
						&& (!only_changed || (only_changed && p->HasChanged()));
			});
	return copy_string(json, buffer_size, json_string);
}

extern "C" void ModifySystemData(int id, const char* value)
{
	SystemDataPool::Instance().SetData(id, value);
}

extern "C" int FetchRecentEventLog(char* json, unsigned buffer_size)
{
	std::string json_string;
	json_string = EventLogger::Instance().FetchLogs();
	return copy_string(json, buffer_size, json_string);
}

extern "C" void Invoke(int unit, int cmd, unsigned param1, unsigned param2)
{

}
