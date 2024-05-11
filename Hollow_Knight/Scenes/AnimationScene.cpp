#include "Framework.h"
#include "AnimationScene.h"

AnimationScene::AnimationScene()
{
	mario = new Mario;
	
	background = new Object(L"background.png");
	background->Pos() = WIN_CENTER;
	background->Scale().x *= 2.0f;

	CAMERA->SetTarget(mario);

}

AnimationScene::~AnimationScene()
{
	delete mario;

	delete background;
	
}

void AnimationScene::Update()
{
	mario->Update();

	background->UpdateWorld();

}

void AnimationScene::Render()
{
	background->Render();

	mario->Render();
}
