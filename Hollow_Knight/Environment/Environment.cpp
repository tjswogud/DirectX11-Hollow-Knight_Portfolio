#include "Framework.h"
#include "Environment.h"

Environment::Environment()
{
	CreateProjection();
	CreateSamplerState();
	CreateBlendState();
	CreateRasterizerState();

	camera = new Camera;
}

Environment::~Environment()
{
	delete pBuffer;
	delete camera;

	samplerState->Release();
}

void Environment::SetAlpha()
{
	DC->OMSetBlendState(alphaBlendState, nullptr, D3D11_DEFAULT_SAMPLE_MASK);
}

void Environment::SetAddtive()
{
	DC->OMSetBlendState(additiveBlendState, nullptr, D3D11_DEFAULT_SAMPLE_MASK);
}

void Environment::CreateProjection()
{
	pBuffer = new MatrixBuffer;

	Matrix projection = XMMatrixOrthographicOffCenterLH
	(
		0, WIN_WIDTH,
		0, WIN_HEIGHT,
		0, 1.0f
	);

	pBuffer->Set(projection);

	pBuffer->SetVSBuffer(2);
}

void Environment::CreateSamplerState()
{
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD = 0; // 시야 기준에서 보여주는 영역 설정
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	DEVICE->CreateSamplerState(&samplerDesc, &samplerState);

	DC->PSSetSamplers(0, 1, &samplerState);
}

void Environment::CreateBlendState()
{
	D3D11_BLEND_DESC blendDesc = {};

	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false; // RenderTarget이 여러개면 사용하게됨, 1개만 사용할거라 false

	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; // 비율로 섞어줘야하기 때문에 
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD; // 위에 두개를 더하겠다 =  SrcBl, DestBl
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; // 특정한색을 제외시킨다.

	DEVICE->CreateBlendState(&blendDesc, &alphaBlendState);

	DC->OMSetBlendState(alphaBlendState, nullptr, D3D11_DEFAULT_SAMPLE_MASK); // PS가 색상을 다 입히면 그때 결정을 내리는 역할

	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE; // ONE으로 바꾸면 배경색 그대로쓰고 + 원본색상 0.7만큼 색이 밝아짐
	DEVICE->CreateBlendState(&blendDesc, &additiveBlendState);
}

void Environment::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.CullMode = D3D11_CULL_NONE; // 뒷면 없애기
	rasterizerDesc.FillMode = D3D11_FILL_SOLID; // 없앤 자리 채우기

	DEVICE->CreateRasterizerState(&rasterizerDesc, &rasterizerState);

	DC->RSSetState(rasterizerState);
}
