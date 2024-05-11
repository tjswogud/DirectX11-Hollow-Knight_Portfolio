#include "Framework.h"
#include "PixelShader.h"

PixelShader::PixelShader(wstring file)
{
    DWORD flag = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    

    file = L"_Shaders/" + file + L".hlsl";

    D3DCompileFromFile
    (
        file.c_str(),
        nullptr,
        nullptr,
        "PS",
        "ps_5_0",
        flag,
        0,
        &pixelBlob,
        nullptr
    );

    DEVICE->CreatePixelShader
    (
        pixelBlob->GetBufferPointer(),
        pixelBlob->GetBufferSize(),
        nullptr,
        &pixelShader
    );

    
}

PixelShader::~PixelShader()
{
    pixelBlob->Release();
    pixelShader->Release();
}

void PixelShader::Set()
{
    DC->PSSetShader(pixelShader, nullptr, 0);
}
