#include "Framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	for (UINT i = 0; i < 2; i++)
	{
		Collider* collider = new ColliderRect(Vector2(100, 200));
		collider->Pos() = WIN_CENTER + Vector2(200 * i, 0);
		collider->SetLabel("ColliderRect" + to_string(i + 1));

		colliders.push_back(collider);
	}

	for (UINT i = 0; i < 2; i++)
	{
		Collider* collider = new ColliderCircle(50);
		collider->Pos() = WIN_CENTER + Vector2(200 * i, 200);
		collider->SetLabel("ColliderCircle" + to_string(i + 1));

		colliders.push_back(collider);
	}
}

CollisionScene::~CollisionScene()
{
	for (Collider* collider : colliders)
		delete collider;
}

void CollisionScene::Update()
{
	if (colliders[0]->Collision(colliders[2]))
		colliders[0]->SetColor(1, 0, 0);
	else		  
		colliders[0]->SetColor(0, 1, 0);

	for (Collider* collider : colliders)
		collider->UpdateWorld();
}

void CollisionScene::Render()
{
	for (Collider* collider : colliders)
	{
		collider->Render();

		ImGui::BeginChild("Colliders", ImVec2(200, 25 * colliders.size()), true);
		collider->Debug();
		ImGui::EndChild();
	}
}

