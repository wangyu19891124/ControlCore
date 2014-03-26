/*
 * Database.cpp
 *
 *  Created on: 2014��3��24��
 *      Author: acm
 */

#include "boost/chrono.hpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"

#include "Database.h"
#include "EventLevel.h"


using namespace boost::chrono;
using namespace boost::property_tree;

void Database::Initialize()
{
	if(m_thrd)
		return;

	std::string hostname = m_cfg_file.Read<std::string>("database/host", "localhost");
	std::string user = m_cfg_file.Read<std::string>("database/user", "acm");
	std::string password = m_cfg_file.Read<std::string>("database/password", "acm");
	std::string database = m_cfg_file.Read<std::string>("database/database", "dry_etch");
	unsigned short port = m_cfg_file.Read<unsigned short>("database/port", 3306);

	mysql_init(&m_mysql);
	if (!mysql_real_connect(&m_mysql, hostname.c_str(), user.c_str(), password.c_str(),
			database.c_str(), port, NULL, 0))
	{
		throw "Connect database failed.";
	}

	m_thrd.reset(new boost::thread([this](){this->do_work();}));
}

void Database::Terminate()
{
	if(!m_thrd)
		return;

	m_thrd->interrupt();
	m_thrd->join();
	m_thrd.reset();

	mysql_close(&m_mysql);
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

void Database::WaferExit(const std::string& id, const std::string& state, const std::string& recipe)
{
	std::stringstream ss;
	ss<<"call wafer_exit('"<<id<<"', '"<<system_clock::now()<<"', '"<<state<<"', '"<<recipe<<"');";

	boost::mutex::scoped_lock lock(m_list_mtx);
	m_sql_list.push_back(ss.str());
}

std::string Database::QueryLog(const time_point& start_time, const time_point& end_time, unsigned level_mask)
{
	std::stringstream ss;
	ss<<"select * from 'dry_etch'.'event_log' where ('time' between '"<<start_time<<"' and '"<<end_time<<"') and ('level' in (";
	if(level_mask & EVENT_LEVEL_DEBUG)
		ss<<"'debug', ";
	if(level_mask & EVENT_LEVEL_INFO)
		ss<<"'info', ";
	if(level_mask & EVENT_LEVEL_WARNING)
		ss<<"'warning', ";
	if(level_mask & EVENT_LEVEL_ERROR)
		ss<<"'error', ";
	if(level_mask & EVENT_LEVEL_CRITICAL)
		ss<<"'critical', ";
	if(level_mask & EVENT_LEVEL_EMERGENCY)
		ss<<"'emergency', ";

	ss<<"'')) order by 'time' desc limit 1000;";
	std::string sql = ss.str();
	ss.str("");
	ss.clear();

	MYSQL_RES* result_set;
	{
		//execute query
		boost::mutex::scoped_lock lock(m_db_mtx);
		int rtv = mysql_query(&m_mysql, sql.c_str());
		if(!rtv)
		{
			//TODO log, report event log

			return "";
		}

		result_set = mysql_store_result(&m_mysql);
	}

	ptree pt;

	int rows = mysql_num_rows(result_set);
//	int fields = mysql_num_fields(result_set);
	MYSQL_ROW row;
	for(int i=0; i<rows; i++)
	{
		row = mysql_fetch_row(result_set);
		ptree pt_child;
		pt.put("Time", row[0]);
		pt.put("ID", row[1]);
		pt.put("Level", row[2]);
		pt.put("Info", row[3]);
		pt.add_child("Log/LogItem", pt_child);
	}
	mysql_free_result(result_set);

	json_parser::write_json(ss, pt);

	return ss.str();
}

std::string Database::QueryData(const time_point& start_time, const time_point& end_time, const std::string& type)
{
	std::stringstream ss;
	ss<<"select * from 'dry_etch'.'process_data' where ('time' between '"<<start_time<<"' and '"<<end_time<<"') and ('type' = '"<<type<<"') order by 'time' incs limit 1000;";
	std::string sql = ss.str();
	ss.str("");
	ss.clear();

	MYSQL_RES* result_set;
	{
		//execute query
		boost::mutex::scoped_lock lock(m_db_mtx);
		int rtv = mysql_query(&m_mysql, sql.c_str());
		if(!rtv)
		{
			//TODO log, report event log

			return "";
		}

		result_set = mysql_store_result(&m_mysql);
	}

	ptree pt;

	int rows = mysql_num_rows(result_set);
//	int fields = mysql_num_fields(result_set);
	MYSQL_ROW row;
	for(int i=0; i<rows; i++)
	{
		row = mysql_fetch_row(result_set);
		ptree pt_child;
		pt.put("Time", row[0]);
		pt.put("Type", row[1]);
		pt.put("Value", row[2]);
		pt.add_child("Data/Item", pt_child);
	}
	mysql_free_result(result_set);

	json_parser::write_json(ss, pt);

	return ss.str();
}

void Database::do_work()
{
	boost::this_thread::disable_interruption di;

	while(true)
	{
		std::string sql;
		{
			boost::mutex::scoped_lock lock(m_list_mtx);
			if(m_sql_list.size() > 0)
			{
				sql = *(m_sql_list.begin());
				m_sql_list.pop_front();
			}
		}
		if(!sql.empty())
		{
			boost::mutex::scoped_lock lock(m_db_mtx);
			int rtv = mysql_query(&m_mysql, sql.c_str());
			if(!rtv)
			{
				//TODO log

			}

			continue;
		}

		if (boost::this_thread::interruption_requested())
			break;

		boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
	}
}
