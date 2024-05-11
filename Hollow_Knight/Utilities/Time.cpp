#include "Framework.h"
#include "Time.h"

Time* Time::instance = nullptr;

double Time::timeElapsed = 0.0;

Time::Time()
	: curTick(0), frameCount(0), frameRate(0), oneSecCount(0), runningTime(0), scanningRate(0)
{
	//�ʴ� CPU ����(tick) ��
	QueryPerformanceFrequency((LARGE_INTEGER*)&ticksPerSecond);

	//������� CPU ����(tick) ���� ��
	QueryPerformanceCounter((LARGE_INTEGER*)&lastTick);

	//1tick�� �ɸ��� �ð�
	timeScale = 1.0 / ticksPerSecond;
}

Time::~Time()
{
}

void Time::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&curTick);

	//1�����ӿ� �ɸ� �ð�(�帥 �ð�)
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

	//1�� üũ�� ���� ����
	oneSecCount += timeElapsed;

	//���α׷� ���� �� ��� �ð�
	runningTime += timeElapsed;

	if (oneSecCount >= 1.0)
	{
		frameRate  = frameCount;
		frameCount = 0;

		oneSecCount = 0;
	}
}
