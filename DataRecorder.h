/*
 * DataRecorder.h
 *
 *  Created on: 2014Äê3ÔÂ20ÈÕ
 *      Author: acm
 */

#ifndef DATARECORDER_H_
#define DATARECORDER_H_

#include <list>

#include "boost/function.hpp"
#include "boost/chrono.hpp"
#include "boost/thread.hpp"
#include "boost/thread/mutex.hpp"
#include "boost/shared_ptr.hpp"

#include "Singleton.h"

enum RecordItemID
{
	RecordItem_N2,
	RecordItem_EtOH,
	RecordItem_HF,
	RecordItem_Pressure,
};

class RecordItem
{
public:
	RecordItem() = delete;
	RecordItem(RecordItemID id, const std::string& name, unsigned interval,
			boost::function<float ()> f, bool enable = false);
	RecordItem(const RecordItem&) = delete;
	~RecordItem() = default;

	RecordItem& operator = (const RecordItem&) = delete;
	bool operator == (const RecordItem&);
	void Enable();
	void Disable();

	void Monitor();
	RecordItemID GetID();

private:
	RecordItemID m_id;
	std::string m_name;
	unsigned m_interval;
	boost::function<float ()> m_f;
	boost::chrono::time_point<boost::chrono::system_clock> m_last_record_time;
	bool m_enable_flag;
};

class DataRecorder : public SingletonT<DataRecorder>
{
protected:
	DataRecorder() = default;
	DataRecorder(const DataRecorder&) = delete;
	DataRecorder& operator = (const DataRecorder&) = delete;
public:
	virtual ~DataRecorder() = default;

	void Initialize();
	void Terminate();
	void Enable(RecordItemID id);
	void Disable(RecordItemID id);
	void Add(boost::shared_ptr<RecordItem> item);
	void Remove(RecordItemID id);

	friend class SingletonT<DataRecorder>;
private:
	void monitor();

private:
	std::list<boost::shared_ptr<RecordItem>> m_items;
	boost::mutex m_mtx;
	boost::scoped_ptr<boost::thread> m_thrd;
};

#endif /* DATARECORDER_H_ */
