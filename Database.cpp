/*
 * Database.cpp
 *
 *  Created on: 2014Äê3ÔÂ24ÈÕ
 *      Author: acm
 */

#include "Database.h"
#include "boost/chrono.hpp"

using namespace boost::chrono;

void Database::Initialize()
{
}

void Database::Terminate()
{
}

void Database::Log(unsigned int id, const std::string& level, const std::string& info)
{
	std::stringstream ss;
	//ss<<boost::chrono::time_fmt(boost::chrono::timezone::local, "%Y-%m-%d %H:%M:%S")<<boost::chrono::system_clock::now();
	ss<<"call add_log('"<<system_clock::now()<<"', "<<id<<", '"<<level<<"', '"<<info<<"');";

	boost::mutex::scoped_lock lock(m_list_mtx);
	m_sql_list.push_back(ss.str());
}

void Database::RecordData(const std::string& name, float data)
{
	std::stringstream ss;
	ss<<"call record_data('"<<system_clock::now()<<"', '"<<name<<"', "<<data<<");";

	boost::mutex::scoped_lock lock(m_list_mtx);
	m_sql_list.push_back(ss.str());
}

void Database::WaferEnter(const std::string& id, unsigned short unit, unsigned short slot, const std::string state)
{
	std::stringstream ss;
	ss<<"call wafer_enter('"<<id<<"', "<<unit<<", "<<slot<<", '"<<system_clock::now()<<"', '"<<state<<"');";

	boost::mutex::scoped_lock lock(m_list_mtx);
	m_sql_list.push_back(ss.str());
}

void Database::WaferExit(const std::string& id, const std::string& state, const std::string& recipe = "")
{
	std::stringstream ss;
	ss<<"call wafer_exit('"<<id<<"', '"<<system_clock::now()<<"', '"<<state<<"', '"<<recipe<<"');";

	boost::mutex::scoped_lock lock(m_list_mtx);
	m_sql_list.push_back(ss.str());
}

void Database::do_work()
{

}
