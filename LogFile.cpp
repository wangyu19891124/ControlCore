/*
 * LogFile.cpp
 *
 *  Created on: 2014Äê3ÔÂ27ÈÕ
 *      Author: acm
 */

#include "LogFile.h"
#include "Utility.h"

using namespace boost::log;

void LogFile::Initialize()
{
	boost::log::register_simple_formatter_factory< boost::log::trivial::severity_level, char >("Severity");
	add_file_log(
		keywords::target = "log",
		keywords::file_name = "log_%2N.log",
		keywords::rotation_size = 10 * 1024 * 1024,
		keywords::max_size = 50 * 10 * 1024 * 1024,
		keywords::format = "[%TimeStamp%]\t<%Severity%>\t(%ThreadID%) : %Message%",
		keywords::auto_flush = true);
	core::get()->set_filter(trivial::severity >= trivial::debug);
	add_common_attributes();
}

void LogFile::Terminate()
{
	core::get()->remove_all_sinks();
}

void LogFile::Write(trivial::severity_level level, const std::string& msg)
{
	BOOST_LOG_SEV(m_lg, level)<<msg;
}
