/*
 * Device.cpp
 *
 *  Created on: 2014Äê2ÔÂ27ÈÕ
 *      Author: acm
 */


#include "Device.h"

const unsigned int MAX_BLOCK_IO_NUM = 1024;

Device::Device()
{
	// TODO Auto-generated constructor stub

}

Device::~Device()
{
	// TODO Auto-generated destructor stub
}

unsigned int Device::Follow(unsigned block, boost::function<void ()> f)
{
	boost::recursive_mutex::scoped_lock lock(m_mtx);
	unsigned token = block * MAX_BLOCK_IO_NUM + m_follower[block].size();
	m_follower[block].push_back(f);
	return token;
}

void Device::Unfollow(unsigned token)
{
	boost::recursive_mutex::scoped_lock lock(m_mtx);

	unsigned block = token/MAX_BLOCK_IO_NUM;
	unsigned index = token%MAX_BLOCK_IO_NUM;
	if(index >= m_follower[block].size())
		return;

	m_follower[block][index].clear();
}

void Device::Notify(unsigned block)
{
	boost::recursive_mutex::scoped_lock lock(m_mtx);
	std::vector<boost::function<void ()>>& notify_list = m_follower[block];

	std::for_each(notify_list.begin(), notify_list.end(),
			[&](boost::function<void ()> p)
			{
				if(p)
					p();
			});
}
