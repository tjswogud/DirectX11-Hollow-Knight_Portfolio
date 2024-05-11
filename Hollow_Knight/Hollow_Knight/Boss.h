#pragma once

class Boss : public Character
{
	enum Boss_State
	{
		IDLE,
		MOVE,
		ATTACK,
		ATTACKEND,
		JUMP,
		JUMPATTACK,
		STUN,
		DEATH

	};

public:
	Boss();
	~Boss();

	void Update();
	void Render();

	void FSM();

	void AddAction();

	void SetAction(Boss_State state);

	void SetIdle();

	Collider* GetBossCollider() { return boss; }

	bool& OnGround() { return onground; }

	int& GetHp() { return hp; }

	float& GetGravity() { return gravity; }

	bool& IsAttack() { return isattack; }

	bool& IsAttacking() { return isattacking; }

	Collider* GetSensor() { return sensor; }

	void SetDir(Knight* knight)
	{
		movedir = knight->Pos() - this->lTranslation;
		movedir.y = 0;
		movedir.Normal();
	}

	void Moves()
	{
		if (movedir.x > 0)
		{
			lTranslation += V_RIGHT * speed * Time::Delta();
			lRotation.y = 0.0f;
		}
		else if (movedir.x < 0)
		{
			lTranslation += V_LEFT * speed * Time::Delta();
			lRotation.y = XM_PI;
		}
	}


	// 보스 점프 중력
	void B_Gravity()
	{
		gravity += 2.8;
		lTranslation += V_DOWN * gravity * Time::Delta();
	}

	//Collider* GetCollider() { return knight; }


private:
	Collider* boss;

	Collider* sensor;

	//Collider* knight;

	Vector2 dir;

	Vector2 movedir;

	float speed;
	float jumpspeed;
	float gravity;
	float time;
	float actiontime;
	float attacktime;
	float attackendtime;
	float jumptime;

	int hp;
	int randomaction;

	Boss_State state = IDLE;

	bool onground;

	bool isset;
	
	bool isattack;

	bool isattacking;
};
