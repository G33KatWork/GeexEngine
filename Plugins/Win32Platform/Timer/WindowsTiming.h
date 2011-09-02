/*
 *  WindowsTiming.h
 *  Physics
 *
 *  Created by Andreas Galauner on 06.05.10.
 *  Copyright 2010 none. All rights reserved.
 *
 */

#ifndef _WINDOWS_TIMING_H_
#define _WINDOWS_TIMING_H_

#include <Timing/TimingInformation.h>
#include <Windows.h>

class WindowsTiming : public TimingInformation
{
public:
	WindowsTiming();
	~WindowsTiming(){};
	
protected:
	unsigned long long getSystemMiliseconds();

private:
	LARGE_INTEGER ticksPerSecond;
};

#endif

