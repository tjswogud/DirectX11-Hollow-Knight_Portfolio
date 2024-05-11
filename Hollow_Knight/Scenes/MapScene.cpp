#include "Framework.h"
#include "MapScene.h"

MapScene::MapScene()
{
	//SkillManager::Get()->Setpoolcount(1);

	knight = new Knight;

	map = new Map;

	enemies = new EnemyManager(2);

	boss = new Boss;

	CAMERA->SetTarget(knight);
	//CAMERA->FreeMode();

	knight->Pos() = Vector2{ 5000, 800 };

	//effect = new Effect(L"knight_slash.png", 2, 2, 4); 

	EFFECT->Add("knight_slash", 30, L"knight_slash.png", 2, 2, 4);

	enemies->GetEnemies()[1]->Pos() = WIN_CENTER;
	enemies->GetEnemies()[1]->UpdateWorld();

	enemies->GetEnemies()[0]->Pos() = Vector2(WIN_WIDTH, WIN_CENTER_Y);
	enemies->GetEnemies()[0]->UpdateWorld();

}

MapScene::~MapScene()
{
	delete knight;
	delete map;
	delete enemies;
	delete boss;

}

void MapScene::Update()
{
	//�̵����

	map->Update();

	knight->Update();

	enemies->Update();

	boss->Update();

	/*if (KEY_DOWN('X'))
		EFFECT->Play("knight_slash", mousePos);*/

	CollisionFloor();

	CollisionSword();

	CollisionSkill();

	CollisionBoss();

	CollisionSkillBoss();

	CollisionEFloor();

	CollisionBossFloor();

}

void MapScene::Render()
{
	//�׸���

	map->Render();

	knight->Render();

	enemies->Render();

	boss->Render();
}

void MapScene::SetTaget()
{
	for (Enemy* enemy : enemies->GetEnemies())
	{
		if (!enemy->IsActive())
			continue;

		//knight->SetTaget(enemy);
	}
}

// knight�� ��� ������ �浹
void MapScene::CollisionFloor()
{
	for (Collider* collider : map->GetFloors())
	{
		Vector2 direction = knight->Pos() - collider->Pos();

		Vector2 leftUp = Vector2(-collider->Size().x, -collider->Size().y).Normal();
		Vector2 leftDown = Vector2(-collider->Size().x, +collider->Size().y).Normal();
		Vector2 rightUp = Vector2(+collider->Size().x, -collider->Size().y).Normal();
		Vector2 rightDown = Vector2(+collider->Size().x, +collider->Size().y).Normal();

		if (collider->Collision(knight->GetCollider()))
		{
			// ���� ��
			if (direction.IsBetween(leftUp, leftDown) && knight->Pos().x < collider->Pos().x)
			{
				posX = collider->Pos().x - collider->Size().x * 0.5;
				knight->Pos().x = posX - knight->GetCollider()->Size().x * 0.51;

			}
			// ������ ��
			else if (direction.IsBetween(rightUp, rightDown) && knight->Pos().x > collider->Pos().x)
			{
				posX = collider->Pos().x + collider->Size().x * 0.5;
				knight->Pos().x = posX + knight->GetCollider()->Size().x * 0.51;

			}
			// ��
			else if (direction.IsBetween(leftUp, rightUp) && knight->Pos().y < collider->Pos().y)
			{
				//knight->GetGravity() += 1.8 * Time::Delta();
				//knight->GetGravity() = 0;

				posY = collider->Pos().y - (collider->Size().y * 0.5);
				knight->Pos().y = posY - (knight->GetCollider()->Size().y * 0.51);
				knight->OnGround() = true;

			}
			// �ٴ�
			else if (direction.IsBetween(leftDown, rightDown) && knight->Pos().y > collider->Pos().y)
			{
				knight->GetGravity() = 0;

				if (KEY_DOWN('Z') || KEY_PRESS('Z')) return;
				posY = collider->Pos().y + (collider->Size().y * 0.5);
				knight->Pos().y = posY + (knight->GetCollider()->Size().y * 0.5);

				knight->OnGround() = true;
			}
		}
	}
}



//knight�� �ٴ� �浹 �� ��� ���� �浹
//void MapScene::CollisionFloor()
//{
//	for (Collider* collider : map->GetFloors())
//	{
//		// �ٴ�
//		if (collider->Collision(knight->GetCollider()) && collider->Pos().y < knight->Pos().y) // GetFloors �� vector�̸�, ������ �Ϸ��� ���ȣ�� ����
//		{
//			knight->GetGravity() = 0;
//
//			if (KEY_DOWN('Z') || KEY_PRESS('Z')) return;
//			posY = collider->Pos().y + (collider->Size().y * 0.5);
//			knight->Pos().y = posY + (knight->GetCollider()->Size().y * 0.5);
//
//			knight->OnGround() = true;
//		}
//
//		// õ��
//		else if (collider->Collision(knight->GetCollider()) && collider->Pos().y > knight->Pos().y)
//		{
//			knight->GetGravity() += 15.8 * Time::Delta();
//
//			posY = collider->Pos().y - (collider->Size().y * 0.5);
//			knight->Pos().y = posY - (knight->GetCollider()->Size().y * 0.53);		
//
//		}
//
//		 �� ����
//		if (collider->Collision(knight->GetCollider()) && collider->Pos().x > knight->Pos().x)
//		{
//			posX = collider->Pos().x - collider->Size().x * 0.5;
//			knight->Pos().x = posX - knight->GetCollider()->Size().x * 0.5;
//
//			//1. knight ��,��,�Ʒ�,�� ���� �� ���� �Ǻ��Ѵ�.
//		}
//	}
//	
//	// enemy�� �ٴڿ� �浹
//	for (Collider* collider : map->GetFloors())
//	{
//		for (Enemy* enemy : enemies->GetEnemies())
//		{
//			if (enemy->GetCollider()->Collision(collider))
//			{
//				enemy->GetGravity() = 0;
//				posY = collider->Pos().y + collider->Size().y * 0.5;
//				enemy->Pos().y = posY + enemy->GetCollider()->Size().y * 0.5;
//
//				enemy->OnGround() = true;
//			}
//		}
//	}
//
//	for (Collider* collider : map->GetFloors())
//	{
//		if (boss->GetBossCollider()->Collision(collider))
//		{
//			posY = collider->Pos().y + collider->Size().y * 0.5;
//			boss->Pos().y = posY + boss->GetBossCollider()->Size().y * 0.5;
//
//			boss->OnGround() = true;
//		}
//	}
//		
//}

 //knight�� sword�� enemy �浹
void MapScene::CollisionSword()
{
	for (Enemy* enemy : enemies->GetEnemies())
	{
		if (knight->GetSwordCollider()->Collision(enemy->GetCollider()))
		{
			knight->GetSwordCollider()->SetColor(1, 0, 0);
			enemy->GetCollider()->SetColor(1, 0, 0);
		}
		else
		{
			knight->GetSwordCollider()->SetColor(0, 1, 0);
			enemy->GetCollider()->SetColor(0, 1, 0);
		}
	}
}

// enemy�� skill �浹
void MapScene::CollisionSkill()
{
	for (Skill* skill : SkillManager::Get()->GetSkills())
	{
		for (Enemy* enemy : enemies->GetEnemies())
		{
			if (skill->GetSkillColiider()->Collision(enemy->GetCollider()))
			{
				skill->GetSkillColiider()->SetColor(1, 0, 0);
				enemy->GetCollider()->SetColor(1, 0, 0);
			}

		}
	}
}

// knight�� boss �浹
void MapScene::CollisionBoss()
{
	if (knight->GetSwordCollider()->Collision(boss->GetBossCollider()))
	{
		knight->GetSwordCollider()->SetColor(1, 0, 0);
		boss->GetBossCollider()->SetColor(1, 0, 0);
	}
	else
	{
		knight->GetSwordCollider()->SetColor(0, 1, 0);
		boss->GetBossCollider()->SetColor(0, 1, 0);
	}
}

// knight_skill �� boss �浹
void MapScene::CollisionSkillBoss()
{
	for (Skill* skill : SkillManager::Get()->GetSkills())
	{
		if (skill->GetSkillColiider()->Collision(boss->GetBossCollider()))
		{
			skill->GetSkillColiider()->SetColor(1, 0, 0);
			boss->GetBossCollider()->SetColor(1, 0, 0);
		}
	}
}

void MapScene::CollisionEFloor()
{
	for (Collider* collider : map->GetFloors())
	{
		for (Enemy* enemy : enemies->GetEnemies())
		{
			enemy->GetCollider()->SetColor(1, 0, 0);
			Vector2 direction = enemy->Pos() - collider->Pos();

			Vector2 leftUp = Vector2(-collider->Size().x, -collider->Size().y).Normal();
			Vector2 leftDown = Vector2(-collider->Size().x, +collider->Size().y).Normal();
			Vector2 rightUp = Vector2(+collider->Size().x, -collider->Size().y).Normal();
			Vector2 rightDown = Vector2(+collider->Size().x, +collider->Size().y).Normal();

			if (direction.IsBetween(leftUp, leftDown) && enemy->Pos().x < collider->Pos().x)
			{
				posX = collider->Pos().x - collider->Size().x * 0.5;
				enemy->Pos().x = posX - enemy->GetCollider()->Size().x * 0.51;
				enemy->OnGround() = true;

			}

			else if (direction.IsBetween(rightUp, rightDown) && enemy->Pos().x > collider->Pos().x)
			{
				posX = collider->Pos().x + collider->Size().x * 0.5;
				enemy->Pos().x = posX + enemy->GetCollider()->Size().x * 0.51;
				enemy->OnGround() = true;

			}

			else if (direction.IsBetween(leftUp, rightUp) && enemy->Pos().y < collider->Pos().y)
			{
				enemy->GetGravity() = 0;
				posY = collider->Pos().y - collider->Size().y * 0.5;
				enemy->Pos().y = posY - enemy->GetCollider()->Size().y * 0.51;

				enemy->OnGround() = true;
			}

			else if (direction.IsBetween(leftDown, rightDown) && enemy->Pos().y > collider->Pos().y)
			{
				posY = collider->Pos().y + collider->Size().y * 0.5;
				enemy->Pos().y = posY + enemy->GetCollider()->Size().y * 0.51;
				enemy->OnGround() = true;

			}
		}
	}
}

void MapScene::CollisionBossFloor()
{
	for (Collider* collider : map->GetFloors())
	{
		if (boss->GetBossCollider()->Collision(collider))
		{
			posY = collider->Pos().y + collider->Size().y * 0.5;
			boss->Pos().y = posY + boss->GetBossCollider()->Size().y * 0.5;
		}
	}
}






