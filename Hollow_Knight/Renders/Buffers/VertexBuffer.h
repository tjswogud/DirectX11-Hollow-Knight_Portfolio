#pragma once

class VertexBuffer
{
public:
    template <typename T>
    VertexBuffer(vector<T> vertices);
    ~VertexBuffer();

    void Set(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

private:
    ID3D11Buffer * vertexBuffer;

    UINT stride;
    UINT offset;
};

template<typename T>
inline VertexBuffer::VertexBuffer(vector<T> vertices)
    :offset(0)
{
    stride = sizeof(T);

    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.ByteWidth = stride * vertices.size();
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = vertices.data(); // 벡터에 주소값을 호출하는 명령어 data()

    DEVICE->CreateBuffer(&bufferDesc, &initData, &vertexBuffer);
}
