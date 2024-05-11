#pragma once

class AttackSlash : public Object
{
public:
	AttackSlash();
	~AttackSlash();

	void Update();
	void Render();


private:
	Collider* collider;

	float attackspeed;
};



