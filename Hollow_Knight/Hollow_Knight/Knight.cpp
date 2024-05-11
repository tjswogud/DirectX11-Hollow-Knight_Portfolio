#include "Framework.h"
#include "Knight.h"

Knight::Knight()
	: speed(450), dashspeed(850), jumpspeed(750), jumpcount(0), gravity(0), time(0), isleft(false), isdash(false), onground(false), skiledir(false), skillspeed(800), attacktime(0), isset(false), ishit(false), knockbackspeed(200), invincibletime(0), hp(100), istop(false)
{
	AddAction();

	lTranslation = Vector2{WIN_CENTER_X, WIN_HEIGHT};

	curAction = actions[IDLE];
	
	curAction->Play();

	collider = new ColliderRect(curAction->GetSize());

	sword = new ColliderRect(curAction->GetSize() * 2.0);

	//EFFECT->Add("knight", 30, L"knight_slash.png", 2, 1);

	//SkillManager::Get()->Setpoolcount(30);

	// IDLE로 돌아온다면 
	//sword->IsActive() = false;
	// 만약에 sword가 안사라진다면
	//sword->Pos() = { -100, -100 };


}

Knight::~Knight()
{
	delete collider;
	delete sword;
	//delete skills;
}

void Knight::Update()
{
	Character::Update();

	//LRWall();

	Gravity();

	OffInvincible();

	collider->SetParent(this);
	collider->UpdateWorld();

	sword->UpdateWorld();

	SkillManager::Get()->Update();
	
	/*if (KEY_DOWN('X'))
		EFFECT->Play("knight", sword->Pos());*/

	SetRotationY();

	FSM();

}

void Knight::Render()
{
	Character::Render();

	collider->Render();

	sword->Render();

	SkillManager::Get()->Render();

	string str = "Hollow_Knight : " + to_string((int)this->Pos().x) + ", " + to_string((int)this->Pos().y);
	ImGui::Text(str.c_str());

	str = "Sword : " + to_string((int)sword->Pos().x) + ", " + to_string((int)sword->Pos().y);
	ImGui::Text(str.c_str());

	str = "Gravity : " + to_string((float)gravity);
	ImGui::Text(str.c_str());

	str = "Knight_Hp : " + to_string((int)hp);
	ImGui::Text(str.c_str());
	
}

void Knight::FSM()
{
	switch (state)
	{
	case Knight::IDLE:
		sword->IsActive() = false;

		if (ishit)
		{
			SetAction(STUN);
		}

		if (KEY_PRESS(VK_LEFT))
		{
			isleft = true;
			SetAction(RUN);
		}

		if (KEY_PRESS(VK_RIGHT))
		{
			isleft = false;
			SetAction(RUN);
		}

		if (KEY_DOWN('Z'))
		{
			onground = false;
			SetAction(JUMP);
		}

		if (KEY_DOWN('C'))
		{
			SetAction(DASH);
		}

		if (KEY_DOWN('X'))
		{
			SetAction(ATTACK);
		}

		if (KEY_PRESS(VK_UP) && KEY_DOWN('X'))
		{
			SetAction(UP_ATTACK);
		}
	
		if (KEY_PRESS('A'))
		{
			SetAction(SKILLHP);
		}

		jumpcount = 1;

		Skills();
		
		break;
	case Knight::RUN:
		Runs();

		if (ishit)
		{
			SetAction(STUN);
		}

		if (KEY_UP(VK_LEFT))
			SetAction(IDLE);
		if (KEY_UP(VK_RIGHT))
			SetAction(IDLE);

		if (KEY_DOWN('Z'))
		{
			onground = false;
			SetAction(JUMP);
		}

		if (KEY_DOWN('C'))
		{
			SetAction(DASH);
			jumpspeed = 0;
		}

		jumpspeed = 850;

		if (KEY_DOWN('X'))
		{
			SetAction(ATTACK);
		}

		//Attacks();

		Skills();

		break;

	case Knight::JUMP:
		if (ishit)
		{
			SetAction(STUN);

		}
		if (KEY_UP('Z'))
		{
			gravity = jumpspeed * 1.2;
		}
		
		Jumping();

		if (onground)
		{
			SetAction(IDLE);
		}

		if (KEY_PRESS(VK_LEFT))
		{
			isleft = true;
			Runs();
		}

		if (KEY_PRESS(VK_RIGHT))
		{
			isleft = false;
			Runs();
		}
		
		if (KEY_DOWN('X'))
		{
			SetAction(ATTACK);
		}

		if (KEY_DOWN('C'))
		{
			SetAction(DASH);
			jumpspeed = 0;
		}

		jumpspeed = 1950; // 대쉬 후 점프 on

		if (KEY_PRESS(VK_UP) && KEY_DOWN('X'))
		{
			SetAction(UP_ATTACK);
		}

		if (KEY_PRESS(VK_DOWN) && KEY_DOWN('X'))
		{
			SetAction(DOWN_ATTACK);
		}
		//Attacks();

		if (KEY_DOWN('Z'))
		{
			SetAction(DOUBLE_JUMP);
		}

		Skills();

		break;

	case Knight::DOUBLE_JUMP:

		if (KEY_PRESS(VK_LEFT))
		{
			isleft = true;
			Runs();
		}

		if (KEY_PRESS(VK_RIGHT))
		{
			isleft = false;
			Runs();
		}

		Jumping();

		if (KEY_UP('Z'))
		{
			gravity = jumpspeed * 1.0;
		}

		if (onground)
		{
			SetAction(IDLE);
		}

		if (KEY_DOWN('Z') && jumpcount < 2)
		{
			onground = false;
			gravity = 0.0f;
			jumpspeed = 1450;
			jumpcount++;

			Jumping();
		}

		break;
	case Knight::ATTACK:
		time += Time::Delta();
		// sword  : on / off 기능 잘하기
		// 피격시 중복되는지 확인
		// imGui로 hp 잘 까이는지 확인
		gravity = jumpspeed * 0.6;
		AppearSword(); // 소드 Rect

		attacktime += Time::Delta();

		if (attacktime > 0.8)
		{
			SetIdle();
			attacktime = 0;
		}

		if (time > 0.3)
		{
			SetIdle();
		}

		/*if (KEY_DOWN('X'))
		{
			if (KEY_PRESS(VK_LEFT))
			{
				lTranslation.x -= 10.0f;
			}
			else if (KEY_PRESS(VK_RIGHT))
			{
				lTranslation.x += 10.0f;
			}
		}*/
		break;
	case Knight::UP_ATTACK:
		time += Time::Delta();
		gravity = jumpspeed * 0.6;
	
		UpSword();

		attacktime += Time::Delta();

		if (attacktime > 0.8)
		{
			SetIdle();
			attacktime = 0;
		}

		if (time > 0.3)
		{
			SetIdle();
		}



		break;
	case Knight::DOWN_ATTACK:
		time += Time::Delta();
		gravity = jumpspeed * 0.6;
		
		UpSword();

		attacktime += Time::Delta();

		if (attacktime > 0.8)
		{
			SetIdle();
			attacktime = 0;
		}

		if (time > 0.3)
		{
			SetIdle();
		}


		break;
	case Knight::DASH:
		time += Time::Delta();
		gravity = 0;

		GoDash();
		
		if (time > 0.5)
		{
			SetIdle();
		}


		break;

	case Knight::SKILL:
		time += Time::Delta();

		if (!isset)
		{
			Knight_Skill();
			isset = true;
		}

		if (time > 0.3)
		{
			isset = false;
			SetIdle();
		}

		break;

	case Knight::SKILLHP:
		time += Time::Delta();

		if (time > 0.5)
		{
			SetIdle();
		}

		break;

	case Knight::STUN:
		time += Time::Delta();

		Knockback();

		if (time > 0.4)
		{
			SetIdle();
			isinvincible = true;
			ishit = false;
		}

		break;
	default:
		break;
	}
}

void Knight::AddAction()
{
	actions.emplace(IDLE, new Animation(L"knight_idle.png", 1, 1, 1));
	actions[IDLE]->SetDefault();

	actions.emplace(RUN, new Animation(L"knight_run.png", 5, 1, 5));
	actions[RUN]->SetPart(0, 1);

	actions.emplace(JUMP, new Animation(L"knight_jump.png", 6, 1, 6));
	actions[JUMP]->SetDefault(Animation::END);

	actions.emplace(ATTACK, new Animation(L"knight_attack.png", 5, 2, 10));
	actions[ATTACK]->SetDefault();

	actions.emplace(DASH, new Animation(L"knight_dash.png", 7, 2, 14));
	actions[DASH]->SetPart(0, 6);

	actions.emplace(SKILL, new Animation(L"knight_skills.png", 7, 2, 14));
	actions[SKILL]->SetPart(0, 6);

	actions.emplace(UP_ATTACK, new Animation(L"knight_upattack.png", 5, 2, 10));
	actions[UP_ATTACK]->SetPart(0, 4);

	actions.emplace(DOWN_ATTACK, new Animation(L"knight_downattack.png", 5, 2, 10));
	actions[DOWN_ATTACK]->SetPart(0, 4);

	actions.emplace(SKILLHP, new Animation(L"knight_hpskill.png", 6, 1, 6));
	actions[SKILLHP]->SetDefault();

	actions.emplace(DOUBLE_JUMP, new Animation(L"knight_doublejump.png", 6, 1, 6));
	actions[DOUBLE_JUMP]->SetDefault(Animation::END);

	actions.emplace(STUN, new Animation(L"knight_stun.png", 1, 2, 2));
	actions[STUN]->SetDefault(Animation::END);

}

void Knight::SetAction(State state)
{
	if (this->state == state)
		return;

	this->state = state;
	curAction = actions[state];
	curAction->Play();
	time = 0;
}

void Knight::SetIdle()
{
	SetAction(IDLE);
}

