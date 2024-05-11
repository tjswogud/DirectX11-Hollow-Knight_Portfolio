#pragma once

class VertexShader
{
public:
	VertexShader(wstring file);
	~VertexShader();

	void Set();

	void CreateInputLayout();

private:
	ID3D11VertexShader * vertexShader;
	ID3D11InputLayout  * inputLayout;

	ID3DBlob * vertexBlob;

	ID3D11ShaderReflection* reflection;
};
