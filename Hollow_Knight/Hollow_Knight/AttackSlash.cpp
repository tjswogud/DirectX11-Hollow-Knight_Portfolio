#include "Framework.h"
#include "AttackSlash.h"

AttackSlash::AttackSlash()
	: Object(L"knight_slash.png"), attackspeed(100)
{

	collider = new ColliderRect({ 100, 100 });
	
}

AttackSlash::~AttackSlash()
{
	delete collider;
}

void AttackSlash::Update()
{
	Object::UpdateWorld();

	collider->SetParent(this);
	collider->UpdateWorld(); // 충돌체
}

void AttackSlash::Render()
{
	Object::Render(); // 이미지

	collider->Render(); // 충돌체
}

