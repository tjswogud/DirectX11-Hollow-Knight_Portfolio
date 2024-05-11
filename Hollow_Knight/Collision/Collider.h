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
	virtual bool Collision(class ColliderRect* rect) = 0; // ���漱�� �Ű������� �ϴ� ���, ������ Ŭ���� �ۿ�����, ���⼭�� ���Ŷ� ����
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
