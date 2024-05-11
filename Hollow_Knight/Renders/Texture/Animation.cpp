#include "Framework.h"
#include "Animation.h"

Animation::Animation(wstring file, UINT frameX, UINT frameY, UINT nFrames, float updateTime)
	: updateTime(updateTime)
{
	if (nFrames == 0)
		nFrames = frameX * frameY;

	for (UINT i = 0; i < nFrames; i++)
	{
		UINT x = i % frameX;
		UINT y = i / frameX;

		Vector2 uvStart = { x        / (float)frameX,       y / (float)frameY };
		Vector2 uvEnd   = { (x  + 1) / (float)frameX, (y + 1) / (float)frameY };

		Frame* frame = new Frame(file, uvStart, uvEnd);
		frames.push_back(frame);
	}
}

Animation::~Animation()
{
	for (Frame* frame : frames)
		delete frame;
}

void Animation::Update()
{
	if (!isPlay)
		return;

	frameTime += Time::Delta();
	 playTime += Time::Delta();

	 if (frameTime < updateTime) // 누적 시간이 어느정도까지 된다면 갱신
		 return;

	 switch (type)
	 {
	 case Animation::END:
		 curPlayIndex++;
		 if (curPlayIndex >= actions.size())
		 {
			 curPlayIndex--;
			 Stop();
		 }
		 break;
	 case Animation::LOOP:
		 ++curPlayIndex %= actions.size();
		 if (curPlayIndex == 0)
			 playTime = 0.0f;
		 break;
	 case Animation::RETURN:
		 if (!isReverse)
		 {
			 curPlayIndex++;
			 if (curPlayIndex >= actions.size() - 1) // 마지막 동작에서 멈추고 돌아와야하기 떄문에 -1
			 {
				 isReverse = true;
				  playTime = 0.0f;
			 }
		 }
		 else
		 {
			 curPlayIndex--;
			 if (curPlayIndex <= 0)
			 {
				 isReverse = false;
				 playTime = 0.0f;
			 }
		 }
		 break;
	 default:
		 break;
	 }

	 frameTime -= updateTime; // 프레임이 밀릴수도 있기 떄문에, 초기화 중요
}

void Animation::Render()
{
	actions[curPlayIndex]->Render();
}

void Animation::Play()
{
	isPlay		 = true;
	isReverse    = false;
	frameTime    = 0.0f;
	playTime     = 0.0f;
	curPlayIndex = 0;
}

void Animation::Stop()
{
	isPlay = false;

	frameTime = 0.0f;
	 playTime = 0.0f;

	 if (EndEvent != nullptr)
		 EndEvent();
}

void Animation::SetDefault(Type type)
{
	this->type = type;

	actions.clear();

	for (UINT i = 0; i < frames.size(); i++)
	{
		actions.push_back(frames[i]);
	} 
}

void Animation::SetPart(int start, int end, Type type)
{
	this->type = type;

	actions.clear();

	if (end > start)
	{
		for (int i = start; i <= end; i++)
		{
			actions.push_back(frames[i]);
		}
	}
	else
	{
		for (int i = start; i >= end; i--)
		{
			actions.push_back(frames[i]);
		}
	}
}

void Animation::SetVector(vector<UINT> vector, Type type)
{
	this->type = type;

	actions.clear();

	for (UINT i = 0; i < vector.size(); i++)
	{
		actions.push_back(frames[vector[i]]);
	}
}
