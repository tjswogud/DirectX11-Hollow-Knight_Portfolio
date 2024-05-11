#pragma once

class EffectManager : public Singleton<EffectManager>
{
public:
	EffectManager();
	~EffectManager();

	void Update();
	void Render();

	void Add(string key, UINT poolCount, wstring file, UINT frameX, UINT frameY, UINT nActions = 0, float updateTime = 0.1f, Effect::Type type = Effect::ADDITIVE);

	void Play(string key, Vector2 pos);
	void Stop(string key);

	void StopAll();

private:
	map<string, vector<Effect*>> effectMap;
};
