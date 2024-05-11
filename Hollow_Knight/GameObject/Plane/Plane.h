#pragma once

class Plane : public Object
{
public:
	Plane();
	~Plane();

	void Update();
	void Render();

	void Move();

private:
	float speed = 100.0f;

	Vector4 color = { 1, 1, 1, 1 };
};
