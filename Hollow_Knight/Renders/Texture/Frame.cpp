#include "Framework.h"
#include "Frame.h"

Frame::Frame(wstring file, Vector2 uvStart, Vector2 uvEnd)
{
    texture = Texture::Add(file);

    Vector2 pos = { 0, 0 };

    size =
    {
        texture->GetSize().x * (uvEnd - uvStart).x,
        texture->GetSize().y * (uvEnd - uvStart).y
    };

    float left = pos.x - size.x * 0.5f;
    float right = pos.x + size.x * 0.5f;
    float top = pos.y + size.y * 0.5f;
    float bottom = pos.y - size.y * 0.5f;

    vertices =
    {
        VertexTexture(Vector2(left,    top), Vector2(uvStart.x, uvStart.y)),
        VertexTexture(Vector2(right,   top), Vector2(uvEnd.x, uvStart.y)),
        VertexTexture(Vector2(left,  bottom), Vector2(uvStart.x,   uvEnd.y)),
        VertexTexture(Vector2(right, bottom), Vector2(uvEnd.x,   uvEnd.y))
    };

    indices =
    {
        0, 1, 2,
        2, 1, 3
    };

    vertexBuffer = new VertexBuffer(vertices);
    indexBuffer = new  IndexBuffer(indices);

    
}

Frame::~Frame()
{
    delete vertexBuffer;
    delete  indexBuffer;
}

void Frame::Render()
{
    vertexBuffer->Set();
    indexBuffer->Set();

    texture->SetPS();

    DC->DrawIndexed(indices.size(), 0, 0);
}
