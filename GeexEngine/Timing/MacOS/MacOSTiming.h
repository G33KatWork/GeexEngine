/*
 *  MacOSTiming.h
 *  Physics
 *
 *  Created by Andreas Galauner on 06.05.10.
 *  Copyright 2010 none. All rights reserved.
 *
 */

#ifndef _MACOS_TIMING_H_
#define _MACOS_TIMING_H_

#include <Timing/TimingInformation.h>
#include <mach/mach_time.h>

class MacOSTiming : public TimingInformation
{
public:
	MacOSTiming();
	~MacOSTiming(){};
	
private:
	mach_timebase_info_data_t machTimebase;

protected:
	unsigned long long getSystemMiliseconds();
};

#endif

