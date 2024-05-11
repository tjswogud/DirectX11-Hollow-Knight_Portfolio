#include "Framework.h"
#include "Effect.h"

Effect::Effect(wstring file, UINT frameX, UINT frameY, UINT nActions, float updateTime, Type type)
	:type(type)
{
	vertexShader = new VertexShader(L"VertexTexture");
	pixelShader = new  PixelShader(L"PixelTexture");

	worldBuffer = new MatrixBuffer;
	colorBuffer = new  ColorBuffer;

	animation = new Animation(file, frameX, frameY, nActions, updateTime);
	animation->SetDefault(Animation::END);
	animation->SetEndEvent(bind(&Effect::Stop, this));

	isActive = false;
}

Effect::~Effect()
{
	delete animation;

	delete vertexShader;
	delete  pixelShader;

	delete  worldBuffer;
	delete  colorBuffer;
}

void Effect::Update()
{
	if (!isActive)
		return;

	animation->Update();

	UpdateWorld();
}

void Effect::Render()
{
	if (!isActive)
		return;

	worldBuffer->Set(world);
	worldBuffer->SetVSBuffer(0);
	colorBuffer->SetPSBuffer(0);

	vertexShader->Set();
	pixelShader->Set();

	switch (type)
	{
	case Effect::NORMAL:
		animation->Render();
		break;
	case Effect::ADDITIVE:
		Environment::Get()->SetAddtive();
		animation->Render(); // 중간에 Render를 해주고, 아래 SetAlpha로 다시 바꿔준다.
		Environment::Get()->SetAlpha();
		break;
	default:
		break;
	}
}

void Effect::Play(Vector2 pos)
{
	isActive = true;

	lTranslation = pos;

	animation->Play();
}

void Effect::Stop()
{
	isActive = false;
}
