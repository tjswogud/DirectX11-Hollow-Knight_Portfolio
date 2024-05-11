#pragma once

class MapScene : public Scene
{
public:
	MapScene();
	~MapScene();

	virtual void Update() override;
	virtual void Render() override;

	void SetTaget();

	void CollisionFloor();

	void CollisionSword();

	void CollisionSkill();

	void CollisionBoss();

	void CollisionSkillBoss();

	void CollisionEFloor();

	void CollisionBossFloor();

private:
	Knight* knight;

	Map* map;

	EnemyManager* enemies;

	Boss* boss;

	Effect* effect;

	double posX;

	double posY;

};

