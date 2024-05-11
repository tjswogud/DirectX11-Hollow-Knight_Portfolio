#pragma once

class Enemy : public Character
{
	enum Enemy_State
	{
		IDLE,
		MOVE,
		ATTACK,
		DEATH
	};

public:
	Enemy();
	~Enemy();

	void Update();
	void Render();

	void SetDir(Knight* knight)
	{
		movedir = knight->Pos() - this->lTranslation;
		movedir.y = 0;
		movedir.Normal();
	}

	void Move()
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

	void FSM();

	void AddAction();

	bool& IsActive() { return isActive; }

	void SetAction(Enemy_State state);

	void SetIdle();

	Collider* GetCollider() { return collider; }
	Collider* GetSwordCollider() { return sword; }

	bool& OnGround() { return onground; }
	float& GetGravity() { return gravity; }
	float& GetEnemySpeed() { return speed; }

	bool& IsAttack() { return isattack; }
	bool& isAttacking() { return isattacking; }

	Collider* GetSensor() { return esenser; }

	int& GetHp() { return hp; }

	void EKnockback() // Á×¾úÀ»¶§ 
	{
		if (isleft)
			this->lTranslation += V_RIGHT * Time::Delta();
		else
			this->lTranslation += V_LEFT  * Time::Delta();
	}

private:
	Collider* collider;

	Collider* sword;

	Collider* esenser;

	Vector2 movedir;

	Enemy_State state = IDLE;

	float speed;
	float gravity;
	float time;
	float knockbackspeed;
	float actiontime;
	float attacktime;
	int hp;

	bool onground;
	bool isleft;
	bool ishit;
	bool isattack;
	bool isattacking;
};

