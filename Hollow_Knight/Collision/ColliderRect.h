#pragma once

class ColliderRect : public Collider
{
public:
	ColliderRect(Vector2 size);
	~ColliderRect();

	virtual void SetVertex() override;

	virtual bool Collision(Vector2 point) override;
	virtual bool Collision(ColliderRect* rect) override;
	virtual bool Collision(ColliderCircle* circle) override;

	// ���� �̰��� �޾ƿ����� �θ� ���������Լ��� �ҷ��;��Ѵ�.
	// ��ĳ���� ���¿� �Լ��� �ٽ� �����ϰ� ������ش�. (virtual�� �ٿ�ĳ���� �ϴ� ����)
	Vector2 Size() { return { size.x * gScale.x, size.y * gScale.y }; }

private:
	Vector2 size;




};
