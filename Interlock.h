/*
 * Interlock.h
 *
 *  Created on: 2014Äê3ÔÂ17ÈÕ
 *      Author: acm
 */

#ifndef INTERLOCK_H_
#define INTERLOCK_H_

#include "Singleton.h"

class Interlock : public SingletonT<Interlock>
{
protected:
	Interlock() = default;
	Interlock(const Interlock&) = delete;
	Interlock& operator = (const Interlock&) = delete;
public:
	~Interlock() = default;

	void Initialize();
	void Terminate();

};

#endif /* INTERLOCK_H_ */
