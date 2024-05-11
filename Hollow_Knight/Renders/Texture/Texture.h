#pragma once

class Texture
{
private: // �����ڸ� ���� �θ����� ���⋚���� private�� ����
	Texture(ID3D11ShaderResourceView* srv, ScratchImage& image); // ScratchImage �����ͷ� �������� ���� ������ �Ǿ�����
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
