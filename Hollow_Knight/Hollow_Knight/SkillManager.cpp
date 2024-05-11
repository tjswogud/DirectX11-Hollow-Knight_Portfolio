#include "Framework.h"
#include "SkillManager.h"

SkillManager::SkillManager()
{
	
}

SkillManager::~SkillManager()
{
	for (Skill* skill : skills)
		delete skill;

	skills.clear();
}

void SkillManager::Update()
{
	for (Skill* skill : skills)
		skill->Update();
}

void SkillManager::Render()
{
	for (Skill* skill : skills)
		skill->Render();
}

void SkillManager::Launch(Vector2 pos, float skillspeed, bool isleft)
{
	for (Skill* skill : skills)
	{
		if (!skill->IsLaunch())
		{
			skill->Launch(pos, skillspeed, isleft);
			return;
		}
	}
}
