/*
 *  WindowsTiming.cpp
 *  Physics
 *
 *  Created by Andreas Galauner on 06.05.10.
 *  Copyright 2010 none. All rights reserved.
 *
 */

#include <Platform/Windows/Timing/WindowsTiming.h>
#include <cstring>

WindowsTiming::WindowsTiming()
{
	QueryPerformanceFrequency(&ticksPerSecond);
}

unsigned long long WindowsTiming::getSystemMiliseconds()
{
	LARGE_INTEGER ticks;
	QueryPerformanceCounter(&ticks);
	
	return (ticks.QuadPart * 1000) / ticksPerSecond.QuadPart;
}
