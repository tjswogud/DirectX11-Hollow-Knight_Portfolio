#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	plane = new Plane();
}

TextureScene::~TextureScene()
{
	delete plane;
}

void TextureScene::Update()
{
	plane->Update();
}

void TextureScene::Render()
{
	plane->Render();
}
