#pragma once

class Character : public Transform
{
public:
	Character();
	~Character();

	virtual void Update();
	virtual void Render();

	ColorBuffer* GetColorBuffer() { return colorBuffer; }
protected:
	VertexShader* vertexShader;
	  PixelShader* pixelShader;

	MatrixBuffer* worldBuffer;
	 ColorBuffer* colorBuffer;

	   map<int, Animation*> actions;
	 Animation* curAction = nullptr;

};


