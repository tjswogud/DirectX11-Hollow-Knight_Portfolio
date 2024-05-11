#include "Framework.h"
#include "Enemy.h"

Enemy::Enemy()
	: speed(200), gravity(0), onground(false), time(0), knockbackspeed(200), actiontime(0), attacktime(0), hp(50), isleft(false), ishit(false), isattack(false), isattacking(false)
{
	AddAction();

	lTranslation = { 2000,600 };

	curAction = actions[IDLE];

	curAction->Play();

	collider = new ColliderRect(curAction->GetSize());

	esenser = new ColliderRect(curAction->GetSize() * 2.0);
}

Enemy::~Enemy()
{
	delete collider;
	delete esenser;
}

void Enemy::Update()
{
	Character::Update();

	//time += Time::Delta();

	collider->SetParent(this);
	//collider->Pos() = this->Pos();
	collider->UpdateWorld();

	esenser->SetParent(this);
	esenser->UpdateWorld();

	FSM();
}

void Enemy::Render()
{
	Character::Render();

	collider->Render();

	string str = "Beetle : " + to_string((int)this->Pos().x) + ", " + to_string((int)this->Pos().y);
	ImGui::Text(str.c_str());

	str = "Beetle_Hp : " + to_string((int)hp);
	ImGui::Text(str.c_str());

	str = "Beetle_Move_Dir : " + to_string(int(this->movedir.x));
	ImGui::Text(str.c_str());
}

void Enemy::FSM()
{
	switch (state)
	{
	case Enemy::IDLE:
		actiontime += Time::Delta();
		esenser->IsActive() = false;
		
		if (actiontime > 4.0)
		{
			actiontime = 0;

			SetAction(MOVE);
		}

		if (hp <= 0)
		{
			SetAction(DEATH);
		}

		break;
	case Enemy::MOVE:
		esenser->IsActive() = false;

		Move();

		if (isattack)
		{
			SetAction(ATTACK);
		}

		/*if (lRotation.y == 0.0f)
		{
			lTranslation += V_LEFT * speed * Time::Delta();
		}
		else
		{
			lTranslation += V_RIGHT * speed * Time::Delta();
		}*/
		
		/*if (time > 6.0)
			SetAction(ATTACK);*/
		break;
	case Enemy::ATTACK:
		attacktime += Time::Delta();
		isattacking = true;

		if (attacktime > 0.9)
		{
			attacktime = 0;
			isattack = false;
			isattacking = false;
			SetAction(IDLE);
		}
		/*lTranslation += V_RIGHT * Time::Delta();

		if (time > 10.0)
		{
			SetAction(IDLE);
			time = 0;
			lRotation.y = XM_PI;
		}*/

		break;
	case Enemy::DEATH:

		EKnockback();

		break;
	default:
		break;
	}
}

void Enemy::AddAction()
{
	actions.emplace(IDLE, new Animation(L"beetle_idle.png", 7, 2, 14));
	actions[IDLE]->SetPart(0, 4);

	actions.emplace(MOVE, new Animation(L"beetle_move.png", 7, 2, 14));
	actions[MOVE]->SetPart(0, 5);

	actions.emplace(ATTACK, new Animation(L"beetle_attack.png", 4, 2, 8));
	actions[ATTACK]->SetPart(0, 3);

	actions.emplace(DEATH, new Animation(L"beetle_death.png", 9, 1, 9));
	actions[DEATH]->SetPart(0, 4);
}

void Enemy::SetAction(Enemy_State state)
{

	if (this->state == state)
		return;

	this->state = state;
	curAction = actions[state];
	curAction->Play();
}

void Enemy::SetIdle()
{
	SetAction(IDLE);
}
