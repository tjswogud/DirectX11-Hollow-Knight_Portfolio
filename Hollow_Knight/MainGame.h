#pragma once

class MainGame
{
public:
	MainGame();
	~MainGame();

	void Update();
	void Render();

private:
	Scene* scene;	
};
