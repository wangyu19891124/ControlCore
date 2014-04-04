#pragma once

#include <list>

#include "boost/thread/mutex.hpp"
#include "boost/tuple/tuple.hpp"

#include "Singleton.h"
#include "EventLevel.h"

class EventLogger : public SingletonT<EventLogger>
{
	typedef boost::tuple<std::string, unsigned int, EventLevel, std::string> LogItem;
protected:
	EventLogger();
	EventLogger(const EventLogger&) = delete;
	EventLogger& operator = (const EventLogger&) = delete;
public:
	~EventLogger() = default;

	void Initialize();
	void Terminate();
	void SetFilter(unsigned int filter);
	void Log(unsigned int evt_id, EventLevel evt_level, const std::string& info);
	std::string FetchLogs();

	friend class SingletonT<EventLogger>;

private:
	std::string event_level_to_string(EventLevel level);

private:
	boost::mutex m_mtx;
	unsigned int m_filter;
	std::list<LogItem> m_logs;
};

