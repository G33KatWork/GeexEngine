/*
 *  MacOSTiming.cpp
 *  Physics
 *
 *  Created by Andreas Galauner on 06.05.10.
 *  Copyright 2010 none. All rights reserved.
 *
 */

#include <Timing/MacOS/MacOSTiming.h>
#include <cstring>

MacOSTiming::MacOSTiming()
{
	memset(&machTimebase, 0, sizeof(machTimebase));
}

unsigned long long MacOSTiming::getSystemMiliseconds()
{
	uint64_t time = mach_absolute_time();
	
	if(machTimebase.denom == 0)
		mach_timebase_info(&machTimebase);
	
	return time * machTimebase.numer / machTimebase.denom / 1000;
}
