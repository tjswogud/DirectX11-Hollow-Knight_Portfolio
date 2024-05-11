#pragma once

class TutorialScene : public Scene
{
public:
	TutorialScene();
	~TutorialScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	vector<Object*> rects;

	MatrixBuffer * wBuffer;
	

	XMFLOAT4X4 wMatrix;
	XMFLOAT4X4 wMatrix2;
};
