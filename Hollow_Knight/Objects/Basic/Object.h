#pragma once

class Object : public Transform
{
public:
	Object(Vector2 pos, Vector2 size);
	Object(wstring file, Vector2 uvStart = Vector2(0, 0), Vector2 uvEnd = Vector2(1, 1));
	virtual ~Object();
	
	virtual void Render();

	void SetColorBuffer(Vector4 color) { this->colorBuffer->Set(color); }

private:
	VertexShader* vertexShader;
	 PixelShader*  pixelShader;

	VertexBuffer* vertexBuffer;
	 IndexBuffer*  indexBuffer;

	MatrixBuffer*  worldBuffer;
	 ColorBuffer*  colorBuffer;

	vector<VertexTexture> vertices;
	vector<UINT>		  indices;

	Texture* texture;
};
