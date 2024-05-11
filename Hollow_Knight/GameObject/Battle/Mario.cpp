#include "Framework.h"
#include "Mario.h"

Mario::Mario()
{
	AddAction();

	lTranslation = WIN_CENTER;
	
	curAction = actions[IDLE];
	curAction->Play(); // 시작하면 바로 IDLE 시작
}

Mario::~Mario()
{
}

void Mario::Update()
{
	Character::Update();

	if (KEY_PRESS(VK_LEFT))
	{
		SetAction(RUN);
		lTranslation += V_LEFT * speed * Time::Delta();

		lRotation.y = 0.0f;

	}

	if (KEY_PRESS(VK_RIGHT))
	{
		SetAction(RUN);
		lTranslation += V_RIGHT * speed * Time::Delta();

		lRotation.y = XM_PI; // 뒤집힘
	}

	if (KEY_UP(VK_LEFT) || KEY_UP(VK_RIGHT))
		SetAction(IDLE);

	if (KEY_DOWN(VK_SPACE))
		SetAction(SPIN);
}

void Mario::Render()
{
	Character::Render();
}

void Mario::AddAction()
{
	actions.emplace(IDLE, new Animation(L"mario_all.png", 8, 4, 31));
	actions[IDLE]->SetPart(28, 29); 

	actions.emplace(RUN, new Animation(L"mario_all.png", 8, 4, 31));
	actions[RUN]->SetPart(13, 15);

	actions.emplace(SPIN, new Animation(L"mario_all.png", 8, 4, 31));
	actions[SPIN]->SetVector({ 28, 27, 24, 26 }, Animation::END);
	actions[SPIN]->SetEndEvent(bind(&Mario::SetIdle, this));
}

void Mario::SetAction(State state)
{
	if (this->state == state)
		return;

	this->state = state;
	curAction = actions[state];
	curAction->Play();
}

void Mario::SetIdle()
{
	SetAction(IDLE);
}
