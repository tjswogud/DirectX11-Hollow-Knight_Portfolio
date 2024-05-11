#pragma once

class Effect : public Transform
{
public:
	enum Type
	{
		NORMAL,
		ADDITIVE
	} type;

public:
	Effect(wstring file, UINT frameX, UINT frameY, UINT nActions = 0, float updateTime = 0.1f, Type type = ADDITIVE);
	~Effect();

	void Update();
	void Render();

	void Play(Vector2 pos);
	void Stop();

	void SetLoop() { animation->SetDefault(); }

private:
	Animation* animation;

	VertexShader* vertexShader;
	 PixelShader*  pixelShader;

	MatrixBuffer*  worldBuffer;
	 ColorBuffer*  colorBuffer;
};
