#include "Framework.h"
#include "ColliderRect.h"

ColliderRect::ColliderRect(Vector2 size)
	:size(size)
{
	type = RECT;

	SetVertex();
}

ColliderRect::~ColliderRect()
{
}

void ColliderRect::SetVertex()
{
	float left = -size.x * 0.5f;
	float right = +size.x * 0.5f;
	float top = +size.y * 0.5f;
	float bottom = -size.y * 0.5f;

	vertices =
	{
		Vector2(left,    top),
		Vector2(right,    top),
		Vector2(right, bottom),
		Vector2(left, bottom),
		Vector2(left,    top),
	};

	vertexBuffer = new VertexBuffer(vertices);
}

bool ColliderRect::Collision(Vector2 point)
{
	Matrix invWorld = XMMatrixInverse(nullptr, world);

	Vector2 invPoint = point * invWorld;

	if (abs(invPoint.x) < size.x * 0.5f && abs(invPoint.y) < size.y * 0.5f) // abs = 절대값 반환하는 함수 / 사각형 중점이 0.0 사이즈는 -0.5, +0.5인 상태
		return true;

	return false;
}

bool ColliderRect::Collision(ColliderRect* rect)
{
	Vector2 distance = this->gPosition - rect->gPosition;

	Vector2 axes[4] =
	{
		this->right,
		this->up,
		rect->right,
		rect->up
	};

	Vector2 vectors[4] =
	{
		axes[0] * (this->Size().x * 0.5f),
		axes[1] * (this->Size().y * 0.5f),
		axes[2] * (rect->Size().x * 0.5f),
		axes[3] * (rect->Size().y * 0.5f),
	};
	
	for (UINT i = 0; i < 4; i++)
	{
		float sum = 0;

		for (UINT j = 0; j < 4; j++)
		{
			sum += abs(Vector2::Dot(axes[i], vectors[j]));
		}

		if (sum < abs(Vector2::Dot(axes[i], distance)))
			return false; // 모든 축이 true야 ture기 때문에 하나라도 false면은 return false를 해준다.
	}

	return true;
}

bool ColliderRect::Collision(ColliderCircle* circle)
{
	Vector2 distance = this->gPosition - circle->GlobalPosition();

	Vector2 axes[2] =
	{
		this->right,
		this->up,
	};

	float lengthX = abs(Vector2::Dot(axes[0], distance));
	float lengthY = abs(Vector2::Dot(axes[1], distance));

	float radius = circle->Radius();

	if (lengthX > this->Size().x * 0.5f + radius) return false; // 축과 길이 비교하기
	if (lengthY > this->Size().y * 0.5f + radius) return false;

	if (lengthX < this->Size().x * 0.5f) return true; // 지정된 축을 넘어버린다면 true
	if (lengthY < this->Size().y * 0.5f) return true;

	float x = lengthX - this->Size().x * 0.5f;
	float y = lengthY - this->Size().y * 0.5f;

	return sqrt(pow(x, 2) + pow(y, 2)) < radius;
}
