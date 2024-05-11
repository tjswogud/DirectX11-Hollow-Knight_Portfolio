#pragma once

class EnemyManager
{
public:
	EnemyManager(UINT poolCount);
	~EnemyManager();
	
	void Update();
	void Render();

	vector<Enemy*>& GetEnemies() { return enemies; }
	vector<Collider*> GetEnemys() { return enemys; }

private:
	Knight* target;

	vector<Enemy*> enemies;

	vector<Collider*> enemys;

	float time;
	float randomTime;
};
