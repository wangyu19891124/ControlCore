#pragma once

#define BOOST_CHRONO_VERSION 2
#define BOOST_CHRONO_DONT_PROVIDES_DEPRECATED_IO_SINCE_V2_0_0

#include <deque>

#include "boost/thread.hpp"
#include "boost/thread/mutex.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/scoped_ptr.hpp"
#include "boost/chrono.hpp"

#include "Singleton.h"
#include "Database.h"
#include "EventLevel.h"

class EventLogger : public SingletonT<EventLogger>
{
protected:
	EventLogger() : m_filter(0xFF)
	{
	};
	EventLogger(const EventLogger&) = delete;
	EventLogger& operator = (const EventLogger&) = delete;
public:
	~EventLogger() = default;

	void Initialize()
	{
	}

	void Terminate()
	{
	}

	void SetFilter(unsigned int filter)
	{
		m_filter = filter;
	}

	void Log(unsigned int evt_id, EventLevel evt_level, const std::string& info)
	{
		if (evt_level & m_filter)
		{
			Database::Instance().Log(evt_id, level_to_string(evt_level), info);
		}
	}

	friend class SingletonT<EventLogger>;

private:
	std::string level_to_string(EventLevel level)
	{
		std::string str;
		if(level == EVENT_LEVEL_DEBUG)
			str = "debug";
		else if(level == EVENT_LEVEL_INFO)
			str = "info";
		else if(level == EVENT_LEVEL_WARNING)
			str = "warning";
		else if(level == EVENT_LEVEL_ERROR)
			str = "error";
		else if(level == EVENT_LEVEL_CRITICAL)
			str = "critical";
		else if(level == EVENT_LEVEL_EMERGENCY)
			str = "emergency";

		return str;
	}

private:
	unsigned int m_filter;
};

