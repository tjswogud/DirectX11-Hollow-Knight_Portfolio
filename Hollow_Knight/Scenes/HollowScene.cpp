#include "Framework.h"
#include "HollowScene.h"

HollowScene::HollowScene()
{
	//SkillManager::Get()->Setpoolcount(1);

	knight = new Knight;

	map = new Map;

	enemies = new EnemyManager(2);

	SkillManager::Get()->Setpoolcount(30);

	boss = new Boss;

	knight->Pos() = Vector2{ 8000, 700 };

	boss->Pos() = Vector2{ 8000, 800 };

	CAMERA->SetTarget(knight);
	//CAMERA->FreeMode();

	enemies->GetEnemies()[0]->Pos() = Vector2(2000, 400);
	enemies->GetEnemies()[0]->UpdateWorld();

	enemies->GetEnemies()[1]->Pos() = WIN_CENTER;
	enemies->GetEnemies()[1]->UpdateWorld();



}

HollowScene::~HollowScene()
{
	delete knight;
	delete map;
	delete enemies;
	delete boss;
	
}

void HollowScene::Update()
{
	//이동계산

	map->Update();

	knight->Update();

	enemies->Update();

	boss->Update();

	boss->SetDir(knight);

	/*if (KEY_DOWN('X'))
		EFFECT->Play("knight", knight->Pos());*/

	CollisionFloor();

	CollisionSword();

	CollisionSkill();

	CollisionBoss();

	CollisionSkillBoss();

	CollisionEFloor();

	CollisionBossFloor();

	CollisionBossSenFloor();

	MapChange();
}

void HollowScene::Render()
{
	//그리기
	map->Render();

	enemies->Render();

	boss->Render();

	knight->Render();
}

//void HollowScene::SetTaget()
//{
//	for (Enemy* enemy : enemies->GetEnemies())
//	{
//		if (!enemy->IsActive())
//			continue;
//
//		//knight->SetTaget(enemy);
//	}
//}

// knight와 모든 벽방향 충돌
void HollowScene::CollisionFloor()
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
			// 왼쪽 벽
			if (direction.IsBetween(leftUp, leftDown) && knight->Pos().x < collider->Pos().x)
			{
				posX = collider->Pos().x - collider->Size().x * 0.5;
				knight->Pos().x = posX - knight->GetCollider()->Size().x * 0.51;

			}
			// 오른쪽 벽
			else if (direction.IsBetween(rightUp, rightDown) && knight->Pos().x > collider->Pos().x)
			{
				posX = collider->Pos().x + collider->Size().x * 0.5;
				knight->Pos().x = posX + knight->GetCollider()->Size().x * 0.51;
			
			}
			// 위
			else if (direction.IsBetween(leftUp, rightUp) && knight->Pos().y < collider->Pos().y)
			{
				//knight->GetGravity() += 1.8 * Time::Delta();
				//knight->GetGravity() = 0;

				posY = collider->Pos().y - (collider->Size().y * 0.5);
				knight->Pos().y = posY - (knight->GetCollider()->Size().y * 0.51);
				knight->OnGround() = true;

			}
			// 바닥
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


  //knight와 바닥 충돌 및 모든 방향 충돌
//void HollowScene::CollisionFloor()
//{
//	for (Collider* collider : map->GetFloors())
//	{
//		// 바닥
//		if (collider->Collision(knight->GetCollider()) && collider->Pos().y < knight->Pos().y) // GetFloors 는 vector이며, 접근을 하려면 대괄호로 접근
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
//		// 천장
//		else if (collider->Collision(knight->GetCollider()) && collider->Pos().y > knight->Pos().y)
//		{
//			knight->GetGravity() += 15.8 * Time::Delta();
//
//			posY = collider->Pos().y - (collider->Size().y * 0.5);
//			knight->Pos().y = posY - (knight->GetCollider()->Size().y * 0.53);		
//
//		}
//
//		 // 벽 왼쪽
//		if (collider->Collision(knight->GetCollider()) && collider->Pos().x > knight->Pos().x)
//		{
//			posX = collider->Pos().x - collider->Size().x * 0.5;
//			knight->Pos().x = posX - knight->GetCollider()->Size().x * 0.5;
//
//			//1. knight 왼,오,아래,위 방향 다 만들어서 판별한다.
//		}
//	}
	
	// enemy와 바닥에 충돌
	/*for (Collider* collider : map->GetFloors())
	{
		for (Enemy* enemy : enemies->GetEnemies())
		{
			if (enemy->GetCollider()->Collision(collider))
			{
				enemy->GetGravity() = 0;
				posY = collider->Pos().y + collider->Size().y * 0.5;
				enemy->Pos().y = posY + enemy->GetCollider()->Size().y * 0.5;

				enemy->OnGround() = true;
			}
		}
	}

	for (Collider* collider : map->GetFloors())
	{
		if (boss->GetBossCollider()->Collision(collider))
		{
			posY = collider->Pos().y + collider->Size().y * 0.5;
			boss->Pos().y = posY + boss->GetBossCollider()->Size().y * 0.5;

			boss->OnGround() = true;
		}
	}
		
}*/

 //knight의 sword와 enemy 충돌
void HollowScene::CollisionSword()
{
	for (Enemy* enemy : enemies->GetEnemies())
	{
		// enemy가 공격을 하기 위한 행동
		if (enemy->GetSensor()->Collision(knight->GetCollider()))
		{
			enemy->IsAttack() = true;
		}

		if (knight->IsInvincible()) return;

		if (knight->GetSwordCollider()->Collision(enemy->GetCollider())) 
		{
			attacktime += Time::Delta();
			if (attacktime > 0.5)
			{
				enemy->GetHp() -= 10;
				attacktime = 0;
			}

			knight->GetSwordCollider()->SetColor(1, 0, 0);
			enemy->GetCollider()->SetColor(1, 0, 0);
		}
		else
		{
			knight->GetSwordCollider()->SetColor(0, 1, 0);
			enemy->GetCollider()->SetColor(0, 1, 0);
		}	

		// enemy 무기반경 Rect 
		if (enemy->GetSensor()->Collision(knight->GetCollider()))
		{
			if (enemy->isAttacking())
			{
				knight->IsHit() = true;
				knight->GetHp() -= 10;
				knight->IsInvincible() = true;
			}
		}

		if (knight->GetCollider()->Collision(enemy->GetCollider()))
		{
			knight->GetCollider()->SetColor(1, 0, 0);
			enemy->GetCollider()->SetColor(1, 0, 0);
			knight->IsHit() = true;
			knight->GetHp() -= 10;
			knight->IsInvincible() = true;

		}
		else
			knight->GetCollider()->SetColor(0, 1, 0);
	}
}

// enemy와 skill 충돌
void HollowScene::CollisionSkill()
{
	for (Skill* skill : SkillManager::Get()->GetSkills())
	{
		for (Enemy* enemy : enemies->GetEnemies())
		{
			if (skill->GetSkillColiider()->Collision(enemy->GetCollider()))
			{
				skilltime += Time::Delta();
				if (skilltime > 0.5)
				{
					enemy->GetHp() -= 10;
					skilltime = 0;
				}

				skill->GetSkillColiider()->SetColor(1, 0, 0);
				enemy->GetCollider()->SetColor(1, 0, 0);
			}
		}
	}
}

// knight와 boss 충돌
void HollowScene::CollisionBoss()
{
	// boss가 공격을 하기위한 행동
	if (boss->GetSensor()->Collision(knight->GetCollider()))
	{
		boss->IsAttack() = true;
	}

	if (knight->GetSwordCollider()->Collision(boss->GetBossCollider()))
	{
		boss->GetColorBuffer()->Set(1, 0, 0);

		attacktime += Time::Delta();

		if (attacktime > 0.3)
		{
			boss->GetHp() -= 10;
			attacktime = 0;
		}

		knight->GetSwordCollider()->SetColor(1, 0, 0);
		boss->GetBossCollider()->SetColor(1, 0, 0);
		return;
	}
	else
	{
		boss->GetColorBuffer()->Set(1, 1, 1);
		knight->GetSwordCollider()->SetColor(0, 1, 0);
		boss->GetBossCollider()->SetColor(0, 1, 0);

	}

	if (knight->IsInvincible()) return;

	// boss 무기반경 Rect 
	if (boss->GetSensor()->Collision(knight->GetCollider()))
	{
		if (boss->IsAttacking())
		{
			knight->IsHit() = true;
			knight->GetHp() -= 10;
			knight->IsInvincible() = true;
		}
	}

	// knight가 boss와 충돌시 넉백 및 무적시간 (리스폰)
	if (knight->GetCollider()->Collision(boss->GetBossCollider()))
	{
		knight->GetCollider()->SetColor(1, 0, 0);
		boss->GetBossCollider()->SetColor(1, 0, 0);
		knight->IsHit() = true;
		knight->GetHp() -= 10;
		knight->IsInvincible() = true;
	}
	else
		knight->GetCollider()->SetColor(0, 1, 0);
}

// knight_skill 와 boss 충돌
void HollowScene::CollisionSkillBoss()
{
	for (Skill* skill : SkillManager::Get()->GetSkills())
	{
		if (skill->GetSkillColiider()->Collision(boss->GetBossCollider()))
		{
			boss->GetColorBuffer()->Set(1, 0, 0);

			skilltime += Time::Delta();
			if (skilltime > 0.5)
			{
				boss->GetHp() -= 10;
				skilltime = 0;
			}

			//skill->GetSkillColiider()->IsActive() = false;
			skill->GetSkillColiider()->SetColor(1, 0, 0);
			boss->GetBossCollider()->SetColor(1, 0, 0);
			return;
		}
		else 
			boss->GetColorBuffer()->Set(1, 1, 1);
	}
}

// enemy 바닥 충돌
void HollowScene::CollisionEFloor()
{
	for (Collider* collider : map->GetFloors())
	{
		for (Collider* collider : map->GetFloors())
	{
		for (Enemy* enemy : enemies->GetEnemies())
		{
			if (enemy->GetCollider()->Collision(collider))
			{
				enemy->GetGravity() = 0;
				posY = collider->Pos().y + collider->Size().y * 0.5;
				enemy->Pos().y = posY + enemy->GetCollider()->Size().y * 0.5;

				enemy->OnGround() = true;
			}
		}
	}

	for (Collider* collider : map->GetFloors())
	{
		if (boss->GetBossCollider()->Collision(collider))
		{
			posY = collider->Pos().y + collider->Size().y * 0.5;
			boss->Pos().y = posY + boss->GetBossCollider()->Size().y * 0.5;

			boss->OnGround() = true;
		}
	}
	}
	//for (Collider* collider : map->GetFloors())
	//{
	//	for (Enemy* enemy : enemies->GetEnemies())
	//	{
	//		enemy->GetCollider()->SetColor(1, 0, 0);
	//		Vector2 direction = enemy->Pos() - collider->Pos();

	//		Vector2 leftUp = Vector2(-collider->Size().x, +collider->Size().y).Normal();
	//		Vector2 leftDown = Vector2(-collider->Size().x, -collider->Size().y).Normal();
	//		Vector2 rightUp = Vector2(+collider->Size().x, +collider->Size().y).Normal();
	//		Vector2 rightDown = Vector2(+collider->Size().x, -collider->Size().y).Normal();

	//		if (direction.IsBetween(leftUp, leftDown) && enemy->Pos().x < collider->Pos().x)
	//		{
	//			//posX = collider->Pos().x - collider->Size().x * 0.5;
	//			enemy->Pos().x = (collider->Pos().x - collider->Size().x * 0.5) - enemy->GetCollider()->Size().x * 0.51;
	//			enemy->OnGround() = true;

	//		}

	//		else if (direction.IsBetween(rightUp, rightDown) && enemy->Pos().x > collider->Pos().x)
	//		{
	//			//posX = collider->Pos().x + collider->Size().x * 0.5;
	//			enemy->Pos().x = (collider->Pos().x + collider->Size().x * 0.5) + enemy->GetCollider()->Size().x * 0.51;
	//			enemy->OnGround() = true;

	//		}

	//		else if (direction.IsBetween(leftUp, rightUp) && enemy->Pos().y < collider->Pos().y)
	//		{
	//			enemy->GetGravity() = 0;
	//			//posY = collider->Pos().y - collider->Size().y * 0.5;
	//			enemy->Pos().y = (collider->Pos().y - collider->Size().y * 0.5) - enemy->GetCollider()->Size().y * 0.51;

	//			enemy->OnGround() = true;
	//		}

	//		else if (direction.IsBetween(leftDown, rightDown) && enemy->Pos().y > collider->Pos().y)
	//		{
	//			//posY = collider->Pos().y + collider->Size().y * 0.5;
	//			enemy->Pos().y = (collider->Pos().y + collider->Size().y * 0.5) + enemy->GetCollider()->Size().y * 0.51;
	//			enemy->OnGround() = true;

	//		}
	//	}
	//}
}

// boss 바닥 충돌
void HollowScene::CollisionBossFloor()
{
	for (Collider* collider : map->GetFloors())
	{
		if (boss->GetBossCollider()->Collision(collider))
		{
			// 점프 시작하면 return 아니라면 바닥에 붙음
			boss->GetGravity() = 0;

			if (boss->IsAttacking())
			{
				posY = collider->Pos().y + collider->Size().y * 0.5;
				boss->Pos().y = posY + boss->GetBossCollider()->Size().y * 0.8;
			}

			else
			{
				posY = collider->Pos().y + collider->Size().y * 0.5;
				boss->Pos().y = posY + boss->GetBossCollider()->Size().y * 0.5;
			}

			boss->OnGround() = true;
		}
	}
}

void HollowScene::CollisionBossSenFloor()
{
	for (Collider* collider : map->GetFloors())
	{
		if (boss->GetSensor()->Collision(collider))
		{
			boss->GetGravity() = 0;

			if (boss->IsAttacking())
			{
				posY = collider->Pos().y + collider->Size().y * 0.5;
				boss->Pos().y = posY + boss->GetBossCollider()->Size().y * 0.8;
			}

			else
			{
				posY = collider->Pos().y + collider->Size().y * 0.5;
				boss->Pos().y = posY + boss->GetBossCollider()->Size().y * 0.5;
			}

			boss->OnGround() = true;
		}
	}
}



//for (Collider* collider : map->GetFloors())
//{
//	for (Enemy* enemy : enemies->GetEnemies())
//	{
//		enemy->GetCollider()->SetColor(1, 0, 0);
//		Vector2 direction = enemy->Pos() - collider->Pos();
//
//		Vector2 leftUp = Vector2(-collider->Size().x, +collider->Size().y).Normal();
//		Vector2 leftDown = Vector2(-collider->Size().x, -collider->Size().y).Normal();
//		Vector2 rightUp = Vector2(+collider->Size().x, +collider->Size().y).Normal();
//		Vector2 rightDown = Vector2(+collider->Size().x, -collider->Size().y).Normal();
//
//		if (direction.IsBetween(leftUp, leftDown) && enemy->Pos().x < collider->Pos().x)
//		{
//			//posX = collider->Pos().x - collider->Size().x * 0.5;
//			enemy->Pos().x = (collider->Pos().x - collider->Size().x * 0.5) - enemy->GetCollider()->Size().x * 0.51;
//			enemy->OnGround() = true;
//
//		}
//
//		else if (direction.IsBetween(rightUp, rightDown) && enemy->Pos().x > collider->Pos().x)
//		{
//			//posX = collider->Pos().x + collider->Size().x * 0.5;
//			enemy->Pos().x = (collider->Pos().x + collider->Size().x * 0.5) + enemy->GetCollider()->Size().x * 0.51;
//			enemy->OnGround() = true;
//
//		}
//
//		else if (direction.IsBetween(leftUp, rightUp) && enemy->Pos().y < collider->Pos().y)
//		{
//			enemy->GetGravity() = 0;
//			//posY = collider->Pos().y - collider->Size().y * 0.5;
//			enemy->Pos().y = (collider->Pos().y - collider->Size().y * 0.5) - enemy->GetCollider()->Size().y * 0.51;
//
//			enemy->OnGround() = true;
//		}
//
//		else if (direction.IsBetween(leftDown, rightDown) && enemy->Pos().y > collider->Pos().y)
//		{
//			//posY = collider->Pos().y + collider->Size().y * 0.5;
//			enemy->Pos().y = (collider->Pos().y + collider->Size().y * 0.5) + enemy->GetCollider()->Size().y * 0.51;
//			enemy->OnGround() = true;
//
//		}
//	}
//}

void HollowScene::MapChange()
{
	if (knight->GetCollider()->Collision(map->GetFloors()[15]))
	{
		if (KEY_DOWN(VK_UP))
		{
			knight->Pos() = Vector2{ 8000, 800 };
		}
	}
}