#include "Framework.h"
#include "Time.h"

Time* Time::instance = nullptr;

double Time::timeElapsed = 0.0;

Time::Time()
	: curTick(0), frameCount(0), frameRate(0), oneSecCount(0), runningTime(0), scanningRate(0)
{
	//초당 CPU 진동(tick) 수
	QueryPerformanceFrequency((LARGE_INTEGER*)&ticksPerSecond);

	//현재까지 CPU 진동(tick) 누적 값
	QueryPerformanceCounter((LARGE_INTEGER*)&lastTick);

	//1tick에 걸리는 시간
	timeScale = 1.0 / ticksPerSecond;
}

Time::~Time()
{
}

void Time::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&curTick);

	//1프레임에 걸린 시간(흐른 시간)
	timeElapsed = (curTick - lastTick) * timeScale;

	if (scanningRate != 0)
	{
		while (timeElapsed < (1.0 / scanningRate))
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&curTick);
			timeElapsed = (curTick - lastTick) * timeScale;
		}
	}

	lastTick = curTick;

	frameCount++;

	//1초 체크를 위한 변수
	oneSecCount += timeElapsed;

	//프로그램 시작 후 경과 시간
	runningTime += timeElapsed;

	if (oneSecCount >= 1.0)
	{
		frameRate  = frameCount;
		frameCount = 0;

		oneSecCount = 0;
	}
}
