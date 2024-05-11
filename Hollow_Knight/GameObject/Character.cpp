#include "Framework.h"
#include "Character.h"

Character::Character()
{
	vertexShader = new VertexShader(L"VertexTexture");
	pixelShader = new PixelShader(L"PixelTexture");

	worldBuffer = new MatrixBuffer;
	colorBuffer = new ColorBuffer;

}

Character::~Character()
{
	for (pair<int, Animation*> action : actions)
		delete action.second;

	delete vertexShader;
	 delete pixelShader;
	
	delete worldBuffer;
	delete colorBuffer;
}

void Character::Update()
{
	if (curAction == nullptr)
		return;

	curAction->Update();
	UpdateWorld();
}

void Character::Render()
{
	if (curAction == nullptr)
		return;

	worldBuffer->Set(world);
	worldBuffer->SetVSBuffer(0);
	colorBuffer->SetPSBuffer(0);

	vertexShader->Set();
	pixelShader->Set();

	curAction->Render();

}
