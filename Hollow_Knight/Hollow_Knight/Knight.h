#pragma once

class Knight : public Character
{
	enum State
	{
		IDLE,
		RUN,
		JUMP,
		DOUBLE_JUMP,
		ATTACK,
		UP_ATTACK,
		DOWN_ATTACK,
		DASH,
		SKILL,
		SKILLHP,
		STUN
	};

	enum class LRState
	{
		LEFT,
		RIGHT
	};
	
public:
	Knight();
	~Knight();

	void Update();
	void Render();

	void FSM();

	void AddAction();
	void SetAction(State state);

	void SetIdle();

	void SetTaget(Knight* target) { this->target = target; }

	//void SkillLaunch();

	bool ChackDash() { return isdash; }
	bool& OnGround() { return onground; }
	float& GetGravity() { return gravity; }
	float& GetJumpSpeed() { return jumpspeed; }

	Collider* GetCollider() { return collider; } // privete�� �ɹ������� public�� �Լ��� �����ش�
	Collider* GetSwordCollider() { return sword; }

	int& GetHp() { return hp; }
	bool& IsHit() { return ishit; }
	bool& IsInvincible() { return isinvincible; }

	// ���� �ð�
	void OffInvincible()
	{
		if (isinvincible)
		{
			invincibletime += Time::Delta();
			if (invincibletime > 2.0)
			{
				invincibletime = 0;
				isinvincible = false;
			}
		}
	}

	//SkillManager* GetSkills() { return skills; }

	
	// ���۵� �Լ���
	 
	void Jumping()
	{
		this->lTranslation += V_UP * jumpspeed  * Time::Delta();
	}

	// �ٱ�⺻
	void Runs()
	{
		if (isleft)
			lTranslation += V_LEFT * speed * Time::Delta();
		else
			lTranslation += V_RIGHT * speed * Time::Delta();
	} 

	// �뽬�⺻
	void GoDash()
	{
		if (isleft)
			lTranslation += V_LEFT * dashspeed * Time::Delta();
		else
			lTranslation += V_RIGHT * dashspeed * Time::Delta();
	} 

	// ���ݱ⺻
	/*void Attacks() 
	{
		if (KEY_DOWN('X'))
		{
			SetRotationY();
			SetAction(ATTACK);
		}
	} */

	// ��ų�⺻
	void Skills()
	{
		if (KEY_DOWN('S'))
		{
			SetAction(SKILL);
		}
	}

	/*void SkillsHp()
	{
		if (KEY_PRESS('A'))
		{
			SetAction(SKILLHP);
		}
	}*/

	//��������
	void DoubleJump() 
	{
		if (KEY_DOWN('Z') && jumpcount < 2)
		{
			jumpspeed = 450;
			jumpcount++;

			SetAction(JUMP);

			onground = false;
		}
	}

	// �¿� ����
	void SetRotationY()
	{
		if (isleft)
			lRotation.y = XM_PI;
		else
			lRotation.y = 0.0f;
	}

	// �⺻���� ũ��� ���� ���ϱ�
	void AppearSword()
	{
		sword->IsActive() = true;
		if (isleft)
		{
			sword->Pos().x = this->Pos().x - sword->Size().x * 0.5;
		}
		else
		{
			sword->Pos().x = this->Pos().x + sword->Size().x * 0.5;

		}
		sword->Pos().y = lTranslation.y;
	}

	// �⺻���� ��, �Ʒ�
	void UpSword()
	{
		sword->IsActive() = true;

		if (istop)
		{
			sword->Pos().x = this->Pos().x;
		}
		else
		{
			sword->Pos().x = this->Pos().x;

		}
		sword->Pos().y = lTranslation.y;
	}

	// ��ų ����� ũ��
	void Knight_Skill()
	{
		SkillManager::Get()->Launch(lTranslation, skillspeed, isleft);
	}

	// ���� �߷°�
	void Gravity()
	{
		gravity += 5.8;
		lTranslation += V_DOWN * gravity * Time::Delta();

	}

	// ���� �� ����
	void LRWall()
	{
		if (this->lTranslation.x > WIN_WIDTH)
			this->lTranslation.x = WIN_WIDTH - collider->Size().x * 0.01;

		if (this->lTranslation.x <= 0)
			this->lTranslation.x = collider->Size().x * 0.01;
	}

	void Knockback()
	{
		if (isleft)
			this->lTranslation += V_RIGHT * knockbackspeed * Time::Delta();
		else
			this->lTranslation += V_LEFT * knockbackspeed * Time::Delta();
	}

private:
	Knight* target;

	Collider* collider;

	Collider* sword;
	
	Effect* effect;

	float speed;
	float dashspeed;
	float jumpspeed;
	float jumpcount;
	float gravity;
	float time;
	float skillspeed;
	float attacktime;
	float knockbackspeed; // �˹�
	float invincibletime; // ����
	int hp;

	Vector2 LRDir = V_RIGHT;

	State state = IDLE;

	LRState lrstate = LRState::RIGHT;

	bool isleft;

	bool isdash;

	bool onground; // ĳ���� �� ���� ó��

	bool skiledir;
	
	bool isset;
	
	bool ishit;

	bool isinvincible;

	bool istop;

};
