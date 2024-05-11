#pragma once

class Skill : public Object
{
public:
	Skill();
	~Skill();

	void Update();
	void Render();

	void Move();

	void Launch(Vector2 pos, float skillspeed, bool isleft);

	bool& IsLaunch() { return islaunch; }

	Collider* GetSkillColiider() { return collider; }

private:
	Collider* collider;

	Object* texture;

	float skillspeed;

	bool islaunch;

	bool isleft;
};

