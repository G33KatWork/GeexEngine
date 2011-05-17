/*
 *  TimingInformation.h
 *  Physics
 *
 *  Created by Andreas Galauner on 06.05.10.
 *  Copyright 2010 none. All rights reserved.
 *
 */

#ifndef _TIMING_INFORMATION_H_
#define _TIMING_INFORMATION_H_

#include <Common/GeexEngineExports.h>

class GEEXENGINE_API TimingInformation
{
public:
	TimingInformation();
	virtual ~TimingInformation(){};
	
	void Update();
	
	unsigned long long GetFrameCount() { return frameNumber; }
	unsigned long long GetLastFrameDuration() { return lastFrameDuration; }
	double GetAverageFrameDuration() { return averageFrameDuration; }
	float GetFPS() { return fps; }
	bool IsPaused() { return isPaused; }
	void TooglePause() { isPaused = !isPaused; }
	
private:
	unsigned long long frameNumber;
	unsigned long long lastFrameTimestamp;
	unsigned long long lastFrameDuration;
	
	double averageFrameDuration;
	float fps;
	
	bool isPaused;

protected:
	virtual unsigned long long getSystemMiliseconds() = 0;
};

#endif

