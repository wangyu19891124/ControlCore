/*
 * Database.h
 *
 *  Created on: 2014Äê3ÔÂ24ÈÕ
 *      Author: acm
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include "boost/thread/mutex.hpp"

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
	void WaferEnter(const std::string& id, unsigned short unit, unsigned short slot, const std::string state);
	void WaferExit(const std::string& id, const std::string& state, const std::string& recipe = "");

	friend class SingletonT<Database>;

private:
	void do_work();

private:
	ConfigFile m_cfg_file;
	std::list<std::string> m_sql_list;
	boost::mutex m_list_mtx;
	boost::mutex m_db_mtx;
};

#endif /* DATABASE_H_ */
