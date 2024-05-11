#pragma once

class Environment : public Singleton<Environment>
{
public:
	Environment();
	~Environment();

	Camera* GetCamera() { return camera; }

	void SetAlpha();
	void SetAddtive();

private:
	void CreateProjection();
	void CreateSamplerState();
	void CreateBlendState();
	void CreateRasterizerState();

private:
	MatrixBuffer* pBuffer;

	ID3D11SamplerState* samplerState;

	ID3D11BlendState* alphaBlendState;
	ID3D11BlendState* additiveBlendState; // ±¤¿øÈ¿°ú

	ID3D11RasterizerState* rasterizerState;

	Camera* camera;
};
