#include "Framework.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager(UINT poolCount)
	: time(0), randomTime(0)
{
	for (UINT i = 0; i < poolCount; i++)
	{
		Enemy* enemy = new Enemy();
		enemy->Pos() = Vector2(i * 50 + 100, WIN_CENTER_Y);
		enemies.push_back(enemy);
	};
	
}

EnemyManager::~EnemyManager()
{
	for (Enemy* enemy : enemies)
		delete enemy;

	enemies.clear();
}

void EnemyManager::Update()
{
	/*time++;

	if (time > randomTime)
	{
		time = 0;
		randomTime += 200.0;
	}*/

	for (Enemy* enemy : enemies)
		enemy->Update();

	//enemies[0]->Update();
}

void EnemyManager::Render()
{
	for (Enemy* enemy : enemies)
		enemy->Render();
}


