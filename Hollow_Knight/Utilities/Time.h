#pragma once

class Time
{
private:
	Time();
	~Time();

public:
	static void Create() { instance = new Time; }
	static void Delete() {	delete instance;	}

	static Time* Get()   { return instance; }

	void Update();

	static double Delta() { return timeElapsed; }

	UINT GetFPS() { return frameRate; }

private:
	static Time* instance;

	static double timeElapsed;

	double timeScale;

	INT64  curTick;
	INT64 lastTick;
	INT64 ticksPerSecond;

	UINT frameCount;
	UINT frameRate;

	double runningTime;

	double scanningRate;

	double oneSecCount;
};
