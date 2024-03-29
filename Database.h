/*
 * Database.h
 *
 *  Created on: 2014��3��24��
 *      Author: acm
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include <list>

#include "boost/thread/mutex.hpp"
#include "boost/thread.hpp"
#include "boost/scoped_ptr.hpp"

#include "mysql/mysql.h"

#include "Singleton.h"
#include "ConfigFile.h"

class Database : public SingletonT<Database>
{
	typedef boost::chrono::time_point<boost::chrono::system_clock> time_point;
protected:
	Database() : m_cfg_file("database"){};
	Database(const Database&) = delete;
	Database& operator = (const Database&) = delete;

public:
	virtual ~Database() = default;

	void Initialize();
	void Terminate();
	void Log(unsigned int id, const std::string& level, const std::string& info);
	void RecordData(const std::string& name, float data);
	void WaferEnter(const std::string& id, int unit, unsigned short slot, const std::string state);
	void WaferExit(const std::string& id, const std::string& state);
	void ProcessStart(const std::string& id, int unit, const std::string& recipe = "");
	void ProcessEnd(const std::string& id);
	void CreateWafer(const std::string& id, const std::string& type, const std::string& size);
	void RemoveWafer(const std::string& id);

	std::string QueryLog(const time_point& start_time, const time_point& end_time, unsigned level_mask = 0xFF);
	std::string QueryData(const time_point& start_time, const time_point& end_time, const std::string& name);

	friend class SingletonT<Database>;

private:
	void do_work();

private:
	ConfigFile m_cfg_file;
	std::list<std::string> m_sql_list;
	boost::mutex m_list_mtx;
	boost::mutex m_db_mtx;
	boost::scoped_ptr<boost::thread> m_thrd;

	MYSQL m_mysql;
};

#endif /* DATABASE_H_ */
