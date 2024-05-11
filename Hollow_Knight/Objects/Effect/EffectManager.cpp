#include "Framework.h"
#include "EffectManager.h"

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
	for (pair<string, vector<Effect*>> pair : effectMap)
	{
		for (Effect* effect : pair.second)
		{
			delete effect;
		}
	}
}

void EffectManager::Update()
{
	for (pair<string, vector<Effect*>> pair : effectMap)
	{
		for (Effect* effect : pair.second)
		{
			effect->Update();
		}
	}
}

void EffectManager::Render()
{
	for (pair<string, vector<Effect*>> pair : effectMap)
	{
		for (Effect* effect : pair.second)
		{
			effect->Render();
		}
	}
}

void EffectManager::Add(string key, UINT poolCount, wstring file, UINT frameX, UINT frameY, UINT nActions, float updateTime, Effect::Type type)
{
	if (effectMap.count(key) > 0)
		return;

	vector<Effect*> effects;

	for (UINT i = 0; i < poolCount; i++)
	{
		Effect* effect = new Effect(file, frameX, frameY, nActions, updateTime, type);

		effects.push_back(effect);
	}

	effectMap[key] = effects;
	//effectMap.emplace(key, effects);
}

void EffectManager::Play(string key, Vector2 pos)
{
	if (effectMap.count(key) == 0)
		return;

	for (Effect* effect : effectMap[key])
	{
		if (!effect->IsActive())
		{
			effect->Play(pos);
			return;
		}
	}
}

void EffectManager::Stop(string key)
{
	for (Effect* effect : effectMap[key])
	{		
		effect->Stop();
	}
}

void EffectManager::StopAll()
{
	for (pair<string, vector<Effect*>> pair : effectMap)
	{
		Stop(pair.first);
	}	
}

