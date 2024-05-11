#pragma once

class Frame
{
public:
	Frame(wstring file, Vector2 uvStart = Vector2(0, 0), Vector2 uvEnd = Vector2(1, 1));
	~Frame();

	void Render();

	Vector2 GetSize() { return size; }

private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;

	vector<VertexTexture> vertices;
	vector<UINT>		  indices;

	Texture* texture;

	Vector2 size;
};



