#include "Framework.h"
#include "Collider.h"

Collider::Collider()
{
    vertexShader = new VertexShader(L"VertexLine");
    pixelShader = new  PixelShader(L"PixelLine");

    worldBuffer = new MatrixBuffer();
    colorBuffer = new  ColorBuffer();
    colorBuffer->Set(0, 1, 0);
}

Collider::~Collider()
{
    delete vertexShader;
    delete  pixelShader;

    delete vertexBuffer;

    delete  worldBuffer;
    delete  colorBuffer;
}

void Collider::Render()
{
    if (!isActive)
        return;

    vertexBuffer->Set(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
    vertexShader->Set();
    pixelShader->Set();

    worldBuffer->Set(world);
    worldBuffer->SetVSBuffer(0);

    colorBuffer->SetPSBuffer(0);

    DC->Draw(vertices.size(), 0);
}

bool Collider::Collision(Collider* other)
{
    if (!isActive)
        return false;

    /*switch (other->type)
    {
    case Collider::RECT:
        return Collision((ColliderRect*)other);
        break;
    case Collider::CIRCLE:
        return Collision((ColliderCircle*)other);
        break;
    default:
        break;
    }*/

    /////////////

    /*int n = 0;
    float f = (float)n;

    float f = static_cast<float>(n);*/

    ColliderRect* rect = dynamic_cast<ColliderRect*>(other);

    if (rect != nullptr)
    {
        return Collision(rect);
    }
    else
    {
        ColliderCircle* circle = dynamic_cast<ColliderCircle*>(other);
        return Collision(circle);
    }

    return false;
}

