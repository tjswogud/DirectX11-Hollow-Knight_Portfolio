#include "Framework.h"
#include "Boss.h"

Boss::Boss()
	: speed(100), jumpspeed(950), gravity(0), time(0), actiontime(0), attacktime(0), attackendtime(0), jumptime(0), onground(false), hp(100), randomaction(0), isset(false), isattack(false), isattacking(false)
{
	AddAction();

	lTranslation = WIN_CENTER;

	curAction = actions[IDLE];

	curAction->Play();

	boss = new ColliderRect(curAction->GetSize() * 0.8);

	sensor = new ColliderRect(curAction->GetSize());
}

Boss::~Boss()
{
	delete boss;
	delete sensor;
}

void Boss::Update()
{
	Character::Update();

	//time += Time::Delta();

	B_Gravity();

	boss->SetParent(this);
	boss->UpdateWorld();

	sensor->SetParent(this);
	sensor->UpdateWorld();

	FSM();
}

void Boss::Render()
{
	Character::Render();

	boss->Render();
	sensor->Render();

	string str = "Hollow_Boss : " + to_string((int)this->Pos().x) + ", " + to_string((int)this->Pos().y);
	ImGui::Text(str.c_str());

	str = "Boss_Hp : " + to_string((int)this->hp);
	ImGui::Text(str.c_str());

	str = "Boss_Move_Dir : " + to_string((int)this->movedir.x);
	ImGui::Text(str.c_str());

}

void Boss::FSM()
{
	switch (state)
	{
	case Boss::IDLE:
		actiontime += Time::Delta();
		sensor->IsActive() = false;

		if (actiontime > 4.0)
		{
			actiontime = 0;
			//SetAction((Boss_State)Math::Random(1, 1));
			SetAction((Boss_State)1);
		}

		/*if (hp <= 0)
		{
			SetAction(DEATH);
		}

		if (hp <= 60)
		{
			SetAction(STUN);
		}*/

		break;
	case Boss::MOVE:
		// 7200 < / > 8850
		sensor->IsActive() = true;

		if (lTranslation.x > 7200 && lTranslation.x < 8850)
		{
			Moves();
		}

		if (isattack)
		{
			isattack = false;

			SetAction(ATTACK);
		}	

		break;
	case Boss::ATTACK:
		attacktime += Time::Delta();
		isattacking = true;

		if (attacktime > 0.7) 
		{
			attacktime = 0;
			isattack = false;
			isattacking = false;
			SetAction(IDLE);
			//SetAction(ATTACKEND);

		}


		break;
	case Boss::ATTACKEND:
		attackendtime += Time::Delta();

		if (attackendtime > 0.4)
		{
			attackendtime = 0;
			SetAction(IDLE);
		}

		break;
	case Boss::JUMP:
		jumptime += Time::Delta();
		sensor->IsActive() = true;

		onground = true;

		if (jumptime > 1.8)
		{
			jumptime = 0;

			this->lTranslation += V_UP * jumpspeed * Time::Delta();
			SetAction(JUMPATTACK);
		}

		break;
	case Boss::JUMPATTACK:
		jumptime += Time::Delta();
		isattacking = true;
		onground = true;

		if (jumptime > 0.6)
		{
			//isattack = false;
			isattacking = false;
			jumptime = 0;
			SetAction(IDLE);
		}

		break;
	case Boss::STUN:
		time += Time::Delta();

		if (time > 1.0)
		{
			time = 0;
			SetAction(IDLE);
		}

		break;
	case Boss::DEATH:
		time += Time::Delta();

		if (time > 1.0)
		{
			time = 0;
			boss->Pos() = Vector2{ -2000,-2000 };
		}

		break;
	default:
		break;
	}

}

void Boss::AddAction()
{
	actions.emplace(IDLE, new Animation(L"Boss/boss_idle.png", 5, 2, 10));
	actions[IDLE]->SetPart(0, 4);

	actions.emplace(MOVE, new Animation(L"Boss/boss_move.png", 5, 1, 5));
	actions[MOVE]->SetPart(0, 4);

	actions.emplace(ATTACK, new Animation(L"Boss/boss_attack.png", 3, 2, 6));
	actions[ATTACK]->SetPart(0, 2, Animation::END);

	actions.emplace(ATTACKEND, new Animation(L"Boss/boss_attackend.png", 5, 2, 10));
	actions[ATTACKEND]->SetPart(0, 4);

	actions.emplace(JUMP, new Animation(L"Boss/boss_jump.png", 4, 2, 8));
	actions[JUMP]->SetPart(0, 3);

	actions.emplace(JUMPATTACK, new Animation(L"Boss/boss_jumpattack.png", 2, 2, 4));
	actions[JUMPATTACK]->SetPart(0, 1);

	actions.emplace(STUN, new Animation(L"Boss/boss_stun.png", 5, 2, 10));
	actions[STUN]->SetPart(0, 4);

	actions.emplace(DEATH, new Animation(L"Boss/boss_death.png", 1, 1, 1));
	actions[DEATH]->SetDefault();
}

void Boss::SetAction(Boss_State state)
{
	if (this->state == state)
		return;

	this->state = state;
	curAction = actions[state];
	curAction->Play();
}

void Boss::SetIdle()
{
	SetAction(IDLE);
}
