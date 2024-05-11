#include "Framework.h"
#include "SolarScene.h"

SolarScene::SolarScene()
{
    sun = new Planet(100, 0.001f, 0.001f, 5);
    sun->Pos() = { WIN_CENTER_X, WIN_CENTER_Y };

    earth = new Planet(50, -0.002f, -0.002f, 4, { 0, 0, 1, 1 });
    earth->Pos() = { 150, 150 };
    earth->SetParent(sun);

    moon = new Planet(10, 0.003f, 0.003f, 3, { 1, 1, 0, 1 });
    moon->Pos() = { 50, 50 };
    moon->SetParent(earth);
}

SolarScene::~SolarScene()
{
    delete sun;
    delete earth;
    delete moon;
}

void SolarScene::Update()
{
      sun->Update();
    earth->Update();
     moon->Update();
}

void SolarScene::Render()
{
      sun->Render();
    earth->Render();
     moon->Render();
}
