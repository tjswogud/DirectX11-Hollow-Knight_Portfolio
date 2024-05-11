#pragma once

class Texture
{
private: // 생성자를 따로 부를일이 없기떄문에 private로 닫음
	Texture(ID3D11ShaderResourceView* srv, ScratchImage& image); // ScratchImage 포인터로 받을수가 없게 구조가 되어있음
	~Texture();

public:
	static Texture* Add(wstring file);
	static void Delete();

	void SetPS(UINT slot = 0);
	
	Vector2 GetSize();

private:
	ID3D11ShaderResourceView* srv;

	ScratchImage image;

	static map<wstring, Texture*> textures;
};
