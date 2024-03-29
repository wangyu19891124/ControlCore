/*
 * Worker.cpp
 *
 *  Created on: 2014��3��6��
 *      Author: acm
 */

#include "Worker.h"

void Worker::Initialize()
{
	if(m_init_flag)
		return;

	int thread_count = 4;
	for(int i=0; i<thread_count; i++)
	{
		m_work_thrds.push_back(new boost::thread(boost::bind(&Worker::DoWork, this)));
	}

	m_init_flag = true;
}

void Worker::Terminate()
{
	if(!m_init_flag)
		return;

	for(boost::thread* thrd : m_work_thrds)
	{
		thrd->interrupt();
		thrd->join();
		delete thrd;
	}
	m_work_thrds.clear();

	m_init_flag = false;
}

void Worker::Post(boost::function<void ()> f)
{
	if(!m_init_flag)
		return;

	boost::mutex::scoped_lock lock(mutex_);
	m_jobs.push_back(f);
}

void Worker::DoWork()
{
	boost::this_thread::disable_interruption di;

	while(true)
	{
		boost::function<void ()> f;
		{
			boost::mutex::scoped_lock lock(mutex_);
			if(m_jobs.size() > 0)
			{
				f = m_jobs[0];
				m_jobs.pop_front();
			}
		}
		if(f)
		{
			f();
			continue;
		}

		if (boost::this_thread::interruption_requested())
			break;

		boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
	}
}
