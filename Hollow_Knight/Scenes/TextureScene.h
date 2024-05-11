#pragma once

class TextureScene : public Scene
{
public:
	TextureScene();
	~TextureScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	//ID3D11ShaderResourceView* srv; // texture에 정보를 다룰 객체, shader로 정보를 넘겨준다, shader로부터 이미지 정보를 받아온다.


	Plane* plane;
};
