#pragma once

class SkillManager : public Singleton<SkillManager>
{
public:
	SkillManager();
	~SkillManager();

	void Update();
	void Render();

	void Launch(Vector2 pos, float skillspeed, bool isleft);

	void Setpoolcount(int count) {
		for (UINT i = 0; i < count; i++)
		{
			skills.push_back(new Skill);
		}
	}

	vector<Skill*>& GetSkills() { return skills; }

private:
	vector<Skill*> skills;

	int poolcount = 0;
};

