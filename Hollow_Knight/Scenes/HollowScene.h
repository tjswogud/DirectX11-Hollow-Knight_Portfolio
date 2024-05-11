#pragma once

class HollowScene : public Scene
{
public:
	HollowScene();
	~HollowScene();

	virtual void Update() override;
	virtual void Render() override;

	//void SetTaget();

	void CollisionFloor();

	void CollisionSword();

	void CollisionSkill();

	void CollisionBoss();

	void CollisionSkillBoss();

	void CollisionEFloor();

	void CollisionBossFloor();

	void CollisionBossSenFloor();

	void MapChange();

private:
	Knight* knight;

	Map* map;

	EnemyManager* enemies;

	Boss* boss;

	double posX;

	double posY;

	float skilltime = 1;

	float attacktime = 1;
};

