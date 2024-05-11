#include "Framework.h"
#include "Object.h"

Object::Object(Vector2 pos, Vector2 size)
{
    float left   = pos.x - size.x * 0.5f;
    float right  = pos.x + size.x * 0.5f;
    float top    = pos.y + size.y * 0.5f;
    float bottom = pos.y - size.y * 0.5f;

    vertices =
    {
        VertexTexture(Vector2( left,    top), Vector2(0, 0)),
        VertexTexture(Vector2(right,    top), Vector2(1, 0)),
        VertexTexture(Vector2( left, bottom), Vector2(0, 1)),
        VertexTexture(Vector2(right, bottom), Vector2(1, 1))
    };

    indices =
    {
        0, 1, 2,
        2, 1, 3
    };

    vertexShader = new VertexShader(L"VertexTexture");
     pixelShader = new  PixelShader( L"PixelTexture");

    vertexBuffer = new VertexBuffer(vertices);
     indexBuffer = new  IndexBuffer( indices);

     worldBuffer = new MatrixBuffer();
     colorBuffer = new  ColorBuffer();
}

Object::Object(wstring file, Vector2 uvStart, Vector2 uvEnd)
{
    texture = Texture::Add(file);

    Vector2 pos  = { 0, 0 };
    Vector2 size =
    {
        texture->GetSize().x * (uvEnd - uvStart).x,
        texture->GetSize().y * (uvEnd - uvStart).y
    };

    float left   = pos.x - size.x * 0.5f;
    float right  = pos.x + size.x * 0.5f;
    float top    = pos.y + size.y * 0.5f;
    float bottom = pos.y - size.y * 0.5f;

    vertices =
    {
        VertexTexture(Vector2( left,    top), Vector2(uvStart.x, uvStart.y)),
        VertexTexture(Vector2(right,    top), Vector2(  uvEnd.x, uvStart.y)),
        VertexTexture(Vector2( left, bottom), Vector2(uvStart.x,   uvEnd.y)),
        VertexTexture(Vector2(right, bottom), Vector2(  uvEnd.x,   uvEnd.y))
    };

    indices =
    {
        0, 1, 2,
        2, 1, 3
    };

    vertexShader = new VertexShader(L"VertexTexture");
     pixelShader = new  PixelShader( L"PixelTexture");

    vertexBuffer = new VertexBuffer(vertices);
     indexBuffer = new  IndexBuffer( indices);

     worldBuffer = new MatrixBuffer();
     colorBuffer = new  ColorBuffer();
}

Object::~Object()
{
    delete vertexShader;
    delete  pixelShader;

    delete vertexBuffer;
    delete  indexBuffer;

    delete  worldBuffer;
    delete  colorBuffer;
}

void Object::Render()
{
    vertexBuffer->Set();
     indexBuffer->Set();
    vertexShader->Set();
     pixelShader->Set();

     worldBuffer->Set(world);
     worldBuffer->SetVSBuffer(0);

     colorBuffer->SetPSBuffer(0); // 픽셀로 넘겨줘여한다 색상을 입힐떄

     if (texture != nullptr)
         texture->SetPS();
         
    DC->DrawIndexed(indices.size(), 0, 0); // Draw가 셋팅되기전까지에 그림을 그린다.
}
