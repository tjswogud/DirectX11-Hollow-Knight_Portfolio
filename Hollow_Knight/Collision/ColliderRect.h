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

	// 지금 이것을 받아오려면 부모에 순수가상함수로 불러와야한다.
	// 업캐스팅 상태에 함수를 다시 접근하게 만들어준다. (virtual로 다운캐스팅 하는 느낌)
	Vector2 Size() { return { size.x * gScale.x, size.y * gScale.y }; }

private:
	Vector2 size;




};
