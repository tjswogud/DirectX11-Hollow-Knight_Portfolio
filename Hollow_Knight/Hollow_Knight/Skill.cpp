#include "Framework.h"
#include "Skill.h"

Skill::Skill()
	: Object(L"knight_skill.png"), skillspeed(100), islaunch(false), isleft(false)
{

	collider = new ColliderRect({ 100, 100 });
}

Skill::~Skill()
{
	delete collider;
}

void Skill::Update()
{
	if (!islaunch)
		return;
	
	Move();

	this->UpdateWorld(); // �̹���

	collider->SetParent(this);
	collider->UpdateWorld(); // �浹ü

}

void Skill::Render()
{
	/*if (!islaunch)
		return;*/

	Object::Render(); // �̹���

	collider->Render(); // �浹ü

}

void Skill::Move()
{
	if (isleft)
	{
		lRotation.y = XM_PI;
		lTranslation += V_LEFT * skillspeed * Time::Delta();
	}
	else
	{
		lRotation.y = 0.0f;
		lTranslation += V_RIGHT * skillspeed * Time::Delta();
	}
}

void Skill::Launch(Vector2 pos, float skillspeed, bool isleft)
{
	lTranslation = pos;
	this->skillspeed = skillspeed;
	this->isleft = isleft;

	islaunch = true;

}
