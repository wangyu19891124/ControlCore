/*
 * EventLevel.h
 *
 *  Created on: 2014Äê3ÔÂ26ÈÕ
 *      Author: acm
 */

#ifndef EVENTLEVEL_H_
#define EVENTLEVEL_H_


enum EventLevel : unsigned int
{
	EVENT_LEVEL_DEBUG		= 0x01,
	EVENT_LEVEL_INFO		= 0x02,
	EVENT_LEVEL_WARNING		= 0x04,
	EVENT_LEVEL_ERROR		= 0x08,
	EVENT_LEVEL_CRITICAL	= 0x10,
	EVENT_LEVEL_EMERGENCY	= 0x20,
};


#endif /* EVENTLEVEL_H_ */
