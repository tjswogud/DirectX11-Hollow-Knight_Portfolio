#pragma once

class PixelShader
{
public:
	PixelShader(wstring file);
	~PixelShader();

	void Set();

private:
	ID3D11PixelShader * pixelShader;

	ID3DBlob * pixelBlob;
};
