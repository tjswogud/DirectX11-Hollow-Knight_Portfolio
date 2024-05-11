#include "Framework.h"
#include "VertexShader.h"

VertexShader::VertexShader(wstring file)
{
    DWORD flag = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    

    file = L"_Shaders/" + file + L".hlsl";

    D3DCompileFromFile
    (
        file.c_str(), 
        nullptr, 
        nullptr, 
        "VS",
        "vs_5_0", 
        flag,
        0, 
        &vertexBlob,
        nullptr
    );

    DEVICE->CreateVertexShader
    (
        vertexBlob->GetBufferPointer(), 
        vertexBlob->GetBufferSize(), 
        nullptr, 
        &vertexShader
    );
        
    CreateInputLayout();
}

VertexShader::~VertexShader()
{
    vertexShader->Release();
     inputLayout->Release();
      vertexBlob->Release();
}

void VertexShader::Set()
{
    DC->IASetInputLayout(inputLayout);
    DC->VSSetShader(vertexShader, nullptr, 0);
}

void VertexShader::CreateInputLayout()
{
    /*D3D11_INPUT_ELEMENT_DESC layoutDesc[2] = {};

    layoutDesc[0].SemanticName         = "POSITION";
    layoutDesc[0].SemanticIndex        = 0;
    layoutDesc[0].Format               = DXGI_FORMAT_R32G32B32_FLOAT;
    layoutDesc[0].InputSlot            = 0;
    layoutDesc[0].AlignedByteOffset    = 0;
    layoutDesc[0].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
    layoutDesc[0].InstanceDataStepRate = 0;

    layoutDesc[1].SemanticName         = "UV";
    layoutDesc[1].SemanticIndex        = 0;
    layoutDesc[1].Format               = DXGI_FORMAT_R32G32_FLOAT;
    layoutDesc[1].InputSlot            = 0;
    layoutDesc[1].AlignedByteOffset    = D3D11_APPEND_ALIGNED_ELEMENT;
    layoutDesc[1].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
    layoutDesc[1].InstanceDataStepRate = 0;

    UINT layoutSize = ARRAYSIZE(layoutDesc);*/

    D3DReflect
    (
        vertexBlob->GetBufferPointer(), 
        vertexBlob->GetBufferSize(), 
        IID_ID3D11ShaderReflection,
        (void**)&reflection
    );

    D3D11_SHADER_DESC shaderDesc;
    reflection->GetDesc(&shaderDesc);

    vector<D3D11_INPUT_ELEMENT_DESC> inputLayouts;

    for (UINT i = 0; i < shaderDesc.InputParameters; i++)
    {
        D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
        reflection->GetInputParameterDesc(i, &paramDesc);

        D3D11_INPUT_ELEMENT_DESC elementDesc;
        elementDesc.SemanticName         = paramDesc.SemanticName;
        elementDesc.SemanticIndex        = paramDesc.SemanticIndex;
        elementDesc.InputSlot            = 0;
        elementDesc.AlignedByteOffset    = D3D11_APPEND_ALIGNED_ELEMENT;
        elementDesc.InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
        elementDesc.InstanceDataStepRate = 0;

        if (paramDesc.Mask == 1) // Mask 데이터 크기를 나타내주는데 자세한건 검색
        {
            // 가져온 하나짜리 자료형이 UINT인지 다른 자료형인지 구분해줌
                 if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)  elementDesc.Format = DXGI_FORMAT_R32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  elementDesc.Format = DXGI_FORMAT_R32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
        }
        else if (paramDesc.Mask <= 3)
        {
                 if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)  elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
        }
        else if (paramDesc.Mask <= 7)
        {
                 if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)  elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
        }
        else if (paramDesc.Mask <= 15)
        {
                 if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)  elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        }

        string semantic = paramDesc.SemanticName;

        if (semantic == "POSITION")
            elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;

        inputLayouts.push_back(elementDesc);
    }

    DEVICE->CreateInputLayout
    (
        inputLayouts.data(),
        inputLayouts.size(),
        vertexBlob->GetBufferPointer(),
        vertexBlob->GetBufferSize(),
        &inputLayout
    );
}
