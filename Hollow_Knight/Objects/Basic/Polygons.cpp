#include "Framework.h"
#include "Polygons.h"

Polygons::Polygons(Vector2 pos, float radius, UINT sectorCount, Vector4 color)
{
    vertices.emplace_back(pos, color); // 처음넣은 버텍스가 중점이된다.

    for (UINT i = 0; i < sectorCount; i++)
    {
        float angle = XM_2PI / sectorCount * i;

        Vector2 pos2 =
        {
            cosf(angle) * radius,
            sinf(angle) * radius
        };

        vertices.emplace_back(pos + pos2, color); // vertex 다 찍힘
    }

    for (UINT i = 0; i < sectorCount; i++)
    {
        indices.push_back(0);

        if (i == sectorCount - 1)
        {
            indices.push_back(1);
            indices.push_back(i + 1);

            break;
        }

        indices.push_back(i + 2);
        indices.push_back(i + 1);
    }

    vertexShader = new VertexShader(L"VertexColor");
     pixelShader = new  PixelShader(L"PixelColor");

    vertexBuffer = new VertexBuffer(vertices);
     indexBuffer = new  IndexBuffer( indices);

     worldBuffer = new MatrixBuffer();
}

Polygons::~Polygons()
{
    delete vertexShader;
    delete  pixelShader;

    delete vertexBuffer;
    delete  indexBuffer;

    delete  worldBuffer;
}

void Polygons::Update()
{
    UpdateWorld();
}

void Polygons::Render()
{
    vertexBuffer->Set();
     indexBuffer->Set();
    vertexShader->Set();
     pixelShader->Set();

     worldBuffer->Set(world);
     worldBuffer->SetVSBuffer(0);
         
    DC->DrawIndexed(indices.size(), 0, 0);
}

void Polygons::UpdateWorld()
{
    Transform::UpdateWorld();
}
