#pragma once

class TextureScene : public Scene
{
public:
	TextureScene();
	~TextureScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	//ID3D11ShaderResourceView* srv; // texture�� ������ �ٷ� ��ü, shader�� ������ �Ѱ��ش�, shader�κ��� �̹��� ������ �޾ƿ´�.


	Plane* plane;
};
