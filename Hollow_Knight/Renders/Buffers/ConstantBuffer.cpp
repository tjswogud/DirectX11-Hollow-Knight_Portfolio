#include "Framework.h"
#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(void * data, UINT dataSize)
    :data(data), dataSize(dataSize)
{
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.ByteWidth = dataSize;
    bufferDesc.Usage     = D3D11_USAGE_DEFAULT;
    bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    DEVICE->CreateBuffer(&bufferDesc, nullptr, &cBuffer);
}

ConstantBuffer::~ConstantBuffer()
{
    cBuffer->Release();
}

void ConstantBuffer::SetVSBuffer(UINT slot) // VS셋팅
{
    DC->UpdateSubresource(cBuffer, 0, nullptr, data, 0, 0);  // UpdateSubresource 받은 정보를 buffer의 업데이트를 해준다는 의미
    DC->VSSetConstantBuffers(slot, 1, &cBuffer); // vertexShader의 셋팅 하겠다는 의미
}

void ConstantBuffer::SetPSBuffer(UINT slot)
{
    DC->UpdateSubresource(cBuffer, 0, nullptr, data, 0, 0); // PS셋팅
    DC->PSSetConstantBuffers(slot, 1, &cBuffer);
}

