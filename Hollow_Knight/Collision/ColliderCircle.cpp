#include "Framework.h"
#include "ColliderCircle.h"

ColliderCircle::ColliderCircle(float radius)
	: radius(radius)
{
	type = CIRCLE;

	SetVertex();
}

ColliderCircle::~ColliderCircle()
{
}

void ColliderCircle::SetVertex()
{
	for (UINT i = 0; i <= VERTEX_COUNT; i++)
	{
		float angle = XM_2PI / VERTEX_COUNT * i;

		Vector2 position =
		{
			cosf(angle) * radius,
			sinf(angle) * radius
		};

		vertices.push_back(position);
	}

	vertexBuffer = new VertexBuffer(vertices);
}

bool ColliderCircle::Collision(Vector2 point)
{
	float distance = Vector2::Distance(point, this->gPosition);

	return distance < Radius();
}

bool ColliderCircle::Collision(ColliderRect* rect)
{
	return rect->Collision(this);
}

bool ColliderCircle::Collision(ColliderCircle* circle)
{
	float distance = Vector2::Distance(this->gPosition, circle->gPosition);

	return distance < this->Radius() + circle->Radius();
}
