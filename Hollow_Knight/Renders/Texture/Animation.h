#pragma once

class Animation
{
public:
	enum Type
	{
		END,
		LOOP,
		RETURN
	};

public:
	Animation(wstring file, UINT frameX, UINT frameY, UINT nFrames = 0, float updateTime = 0.1f);
	~Animation();

	void Update();
	void Render();

	void Play();
	void Stop();

	void SetDefault(Type type = LOOP);
	void SetPart(int start, int end, Type type = LOOP);
	void SetVector(vector<UINT> vector, Type type = LOOP);

	void SetEndEvent(function<void()> EndEvent) { this->EndEvent = EndEvent; }

	Vector2 GetSize() { return actions[0]->GetSize(); }

private:
	vector<Frame*> frames;
	vector<Frame*> actions;

	Type type = LOOP;

	UINT curPlayIndex = 0;

	float updateTime = 0.0f;
	float  frameTime = 0.0f;
	float   playTime = 0.0f;

	bool isPlay	   = true;
	bool isReverse = false;

	function<void()> EndEvent;

	Vector2 size;
};

