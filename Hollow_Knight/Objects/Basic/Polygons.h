#pragma once

class Polygons : public Transform
{
public:
	Polygons(Vector2 pos, float radius, UINT sectorCount = 36, Vector4 color = Vector4(1, 0, 0, 1));
	virtual ~Polygons();

	void Update();
	void Render();

	virtual void UpdateWorld() override;

private:
	VertexShader* vertexShader;
	 PixelShader*  pixelShader;

	VertexBuffer* vertexBuffer;
	 IndexBuffer*  indexBuffer;

	MatrixBuffer*  worldBuffer;

	vector<VertexColor> vertices;
	vector<UINT>		 indices;
};
