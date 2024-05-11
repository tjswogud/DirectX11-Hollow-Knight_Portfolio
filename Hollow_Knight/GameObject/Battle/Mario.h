#pragma once

class Mario : public Character
{
	enum State
	{
		IDLE,
		RUN,
		SPIN
	};

public:
	Mario();
	~Mario();

	void Update();
	void Render();

	void AddAction();
	void SetAction(State state);

	void SetIdle();

private:
	float speed = 100.0f;

	State state = IDLE;
	
};


