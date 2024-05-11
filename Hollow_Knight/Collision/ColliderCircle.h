#pragma once

class ColliderCircle : public Collider
{
public:
	ColliderCircle(float radius = 1.0f);
	~ColliderCircle();

	virtual void SetVertex() override;

	virtual bool Collision(Vector2 point) override;
	virtual bool Collision(ColliderRect* rect) override;
	virtual bool Collision(ColliderCircle* circle) override;

	float Radius() { return radius * max(gScale.x, gScale.y); }

	virtual Vector2 Size() { return { size.x * gScale.x, size.y * gScale.y }; }

private:
	const UINT VERTEX_COUNT = 36;

	float radius = 1.0f;

	Vector2 size;


};
