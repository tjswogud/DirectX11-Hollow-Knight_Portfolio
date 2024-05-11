#pragma once

class Camera : public Transform
{
public:
	Camera();
	~Camera();

	void Update();

	void SetTarget(Transform* target) { this->target = target; }

	void FreeMode();

	void TargetMode();

private:
	MatrixBuffer* vBuffer;

	float speed = 100.0f;

	Transform* target = nullptr;

	Vector2 offset = WIN_CENTER;
};


