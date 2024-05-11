#pragma once

class WorldScene : public Scene
{
public:
	WorldScene();
	~WorldScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	Object* rect;

	MatrixBuffer* wBuffer;
	
	XMFLOAT4X4 identity;

	//XMFLOAT4X4 S, R, T;
	Matrix S, R, T;

	Matrix world;
	Matrix world2;

	Vector2 scale;
	float   rotation;
	Vector2 translation;

	Vector2 right;
	Vector2 up;

	float angle;
};
