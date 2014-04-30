/*
 * WaferManager.h
 *
 *  Created on: 2014Äê2ÔÂ24ÈÕ
 *      Author: acm
 */

#ifndef WAFERMANAGER_H_
#define WAFERMANAGER_H_

#include <map>

#include "boost/shared_ptr.hpp"
#include "boost/thread/mutex.hpp"

#include "Wafer.h"
#include "Singleton.h"

const unsigned int DEFAULT_FOUP_MAPPING = 0x1FFFFFF;
const unsigned int ONE_SLOT_MAPPING = 0x1;
const unsigned short MAX_SLOT_NUM = 25;

class WaferManager : public SingletonT<WaferManager>
{
protected:
	WaferManager() : m_count(0) {};
	WaferManager(const WaferManager&) = delete;
	WaferManager& operator = (const WaferManager&) = delete;
public:
	~WaferManager() = default;

	void Initialize();
	void Terminate();

	friend class SingletonT<WaferManager>;

public:
	void CreateWafer(int unit, unsigned short slot, const std::string& id, WaferSize size, WaferType type = WaferType_Product);
	void CreateWafer(int unit, const std::string& casset_id, WaferSize size, WaferType type = WaferType_Product, unsigned int mapping = 0x1);
	void RemoveWafer(int unit, unsigned int mapping = 0x1);

	void Transfer(int src_unit, unsigned short src_slot, int dest_unit, unsigned short dest_slot);
	bool HasWafer(int unit, unsigned short slot = 0);
	WaferSite GetOriginalSite(int unit, unsigned short slot = 0);
	WaferType GetType(int unit, unsigned short slot = 0);
	WaferSize GetSize(int unit, unsigned short slot = 0);
	void ProcessStart(int unit, const std::string& recipe);
	void ProcessEnd(int unit);
	void ProcessAbort(int unit);
	void WaferBroken(int unit, unsigned short slot = 0);

	void SetRoute(int unit, unsigned short slot, const std::list<WaferSite>& route);
	bool HasRoute(int unit, unsigned short slot);
	WaferSite GetNextSite(int unit, unsigned short slot);

	bool IsWaferAllProcessed(int unit, unsigned int mapping = 0x1);
	bool HasWaferUnprocessed(int unit, unsigned int mapping = DEFAULT_FOUP_MAPPING);
	unsigned short GetUnprocessedWaferSlot(int unit, unsigned int mapping = DEFAULT_FOUP_MAPPING);

private:
	std::string generate_wafer_id(const std::string& casset_id);

private:
	std::map<int, boost::shared_ptr<Wafer> > m_wafers;
	boost::mutex m_mtx;
	unsigned int m_count;
};

#endif /* WAFERMANAGER_H_ */
