#pragma once

class AnimationScene : public Scene
{
public:
	AnimationScene();
	~AnimationScene();


	virtual void Update() override;
	virtual void Render() override;

private:
	Mario* mario;

	Object* background;
};

