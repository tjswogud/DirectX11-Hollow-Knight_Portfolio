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

void ConstantBuffer::SetVSBuffer(UINT slot) // VS����
{
    DC->UpdateSubresource(cBuffer, 0, nullptr, data, 0, 0);  // UpdateSubresource ���� ������ buffer�� ������Ʈ�� ���شٴ� �ǹ�
    DC->VSSetConstantBuffers(slot, 1, &cBuffer); // vertexShader�� ���� �ϰڴٴ� �ǹ�
}

void ConstantBuffer::SetPSBuffer(UINT slot)
{
    DC->UpdateSubresource(cBuffer, 0, nullptr, data, 0, 0); // PS����
    DC->PSSetConstantBuffers(slot, 1, &cBuffer);
}

