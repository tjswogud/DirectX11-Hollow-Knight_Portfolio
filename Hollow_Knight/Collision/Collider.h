#pragma once

class Collider : public Transform
{
protected:
	enum Type
	{
		RECT,
		CIRCLE
	};

public:
	Collider();
	virtual ~Collider();

	void Render();

	virtual void SetVertex() = 0;

	bool Collision(Collider* other);

	virtual bool Collision(Vector2 point) = 0;
	virtual bool Collision(class ColliderRect* rect) = 0; // 전방선언 매개변수로 하는 경우, 원래는 클래스 밖에선언, 여기서만 쓸거라서 가능
	virtual bool Collision(class ColliderCircle* circle) = 0;

	void SetColor(float r, float g, float b) { colorBuffer->Set(r, g, b); }

	virtual Vector2 Size() = 0;

	bool& IsActive() { return isActive; }


protected:
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	VertexBuffer* vertexBuffer;

	MatrixBuffer* worldBuffer;
	ColorBuffer* colorBuffer;

	vector<Vertex> vertices;

	bool isActive = true;

	Type type;

};
