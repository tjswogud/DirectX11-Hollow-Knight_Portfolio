#pragma once

class IndexBuffer
{
public:
	IndexBuffer(vector<UINT> indices);
	~IndexBuffer();

	void Set();

private:
	ID3D11Buffer * indexBuffer;
};
