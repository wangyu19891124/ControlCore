/*
 * Wafer.h
 *
 *  Created on: 2014Äê2ÔÂ21ÈÕ
 *      Author: acm
 */

#ifndef WAFER_H_
#define WAFER_H_

#include <list>

#include "boost/chrono.hpp"

enum WaferType
{
	Wafer_Unprocessed,
	Wafer_Processing,
	Wafer_Processed,
	Wafer_Semi_Processed,
	Wafer_Broken,
	Wafer_Dummy,
};

enum WaferSize
{
	WaferSize_8Inch,
	WaferSize_12Inch,
};

typedef std::pair<int, unsigned short> WaferSite;
typedef boost::chrono::time_point<boost::chrono::system_clock> TimePoint;

class Wafer
{
public:
	Wafer(const std::string& casset_id, int unit, unsigned short slot, WaferSize size, WaferType type = Wafer_Unprocessed);
	virtual ~Wafer();

	WaferSite GetOriginalSite();
//	WaferSite GetSite();
	WaferType GetType();
	WaferSize GetSize();
	std::string GetID();

	void Transfer(int dest_unit, unsigned short dest_slot = 0);
	void ProcessStart(const std::string& recipe);
	void ProcessEnd();
	void ProcessAbort();
	void Broken();

	void SetRoute(const std::list<WaferSite>& m_route);
	bool HasRoute();
	WaferSite GetNextSite();

	bool IsProcessed();
	bool IsUnprocessed();
	bool IsDummy();

private:
	std::string m_casset_id;
	int m_original_unit;
	unsigned short m_original_slot;
//	int m_unit;
//	unsigned short m_slot;
	WaferSize m_size;
	WaferType m_type;
	std::string m_recipe;
	TimePoint m_process_start_time;
	TimePoint m_process_end_time;
	std::list<WaferSite> m_route;
};

#endif /* WAFER_H_ */
