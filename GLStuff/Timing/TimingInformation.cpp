/*
 *  TimingInformation.cpp
 *  Physics
 *
 *  Created by Andreas Galauner on 06.05.10.
 *  Copyright 2010 none. All rights reserved.
 *
 */

#include <Timing/TimingInformation.h>
#include <cstring>

TimingInformation::TimingInformation()
{
	frameNumber = 0;
	lastFrameDuration = 0;
	lastFrameTimestamp = 0;
	averageFrameDuration = 0;
	fps = 0;
	
	isPaused = false;
}

void TimingInformation::Update()
{
	if (!isPaused)
		frameNumber++;
	
	unsigned long long curTime = getSystemMiliseconds();
	
	//Update frame time
	lastFrameDuration = curTime - lastFrameTimestamp;
	lastFrameTimestamp = curTime;
	
	//Update framerates
	if (frameNumber > 1)
	{
		if (averageFrameDuration <= 0)
			averageFrameDuration = (double)lastFrameDuration;
		else
		{
			averageFrameDuration *= 0.99;
			averageFrameDuration += 0.01 * (double)lastFrameDuration;
			
			fps = (float)(1000.0/averageFrameDuration);
		}

	}
}
