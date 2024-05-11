#include "Framework.h"
#include "Planet.h"

Planet::Planet(float radius, float rotationSpeed, float revolutionSpeed, UINT sectorCount, Vector4 color)
    :Polygons({ 0, 0 }, radius, sectorCount, color), rotationSpeed(rotationSpeed), revolutionSpeed(revolutionSpeed), revolutionAngle(0)
{
}

Planet::~Planet()
{
}

void Planet::UpdateWorld()
{
    S = XMMatrixScaling(lScale.x, lScale.y, 1.0f);
    R = XMMatrixRotationRollPitchYaw(lRotation.x, lRotation.y, lRotation.z);
    T = XMMatrixTranslation(lTranslation.x, lTranslation.y, 0.0f);

    world = S * R * T;

    if (parent != nullptr)
    {
        Matrix revolution = XMMatrixRotationZ(revolutionAngle);

        XMFLOAT4X4 pWorld;

        XMStoreFloat4x4(&pWorld, parent->GetWorld());

        Matrix pTranslation = XMMatrixTranslation(pWorld._41, pWorld._42, 0);

        world *= revolution * pTranslation;
    }
}

void Planet::Update()
{
        lRotation.z += rotationSpeed;
    revolutionAngle += revolutionSpeed;

    UpdateWorld();
}

