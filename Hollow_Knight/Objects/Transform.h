#pragma once

class Transform
{
public:
	Transform();
	virtual ~Transform();

	virtual void UpdateWorld();

	void SetParent(Transform* parent) { this->parent = parent; }

	Vector2& Scale() { return lScale; }
	Vector3& Rotation() { return lRotation; }
	Vector2& Pos() { return lTranslation; }

	Vector2& Right() { return right; }
	Vector2& Up() { return up; }

	Matrix GetWorld() { return world; }

	void SetPivot(Vector2 pivot) { this->pivot = pivot; }

	void Debug();

	void SetLabel(string label) { this->label = label; }

	Vector2 GlobalPosition() { return gPosition; }
	Vector2 GlobalScale()    { return gScale;    } 

	bool& IsActive() { return isActive; }

protected:
	Vector2 lScale;
	Vector3 lRotation;
	Vector2 lTranslation;

	Matrix S, R, T;
	Matrix world;

	Transform* parent;

	bool isActive = true;

	XMFLOAT4X4 fWorld;

	Vector2 up, right;

	Vector2 pivot;

	Matrix P, IP; // 행렬 역행렬

	string label;

	Vector2 gScale, gPosition;
};
