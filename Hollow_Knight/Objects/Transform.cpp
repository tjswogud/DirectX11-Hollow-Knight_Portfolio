#include "Framework.h"
#include "Transform.h"

Transform::Transform()
    :lScale(1, 1), lRotation(0, 0, 0), lTranslation(0, 0), parent(nullptr), isActive(true)
{
    S = XMMatrixIdentity();
    R = XMMatrixIdentity();
    T = XMMatrixIdentity();
    world = XMMatrixIdentity();
}

Transform::~Transform()
{
}

void Transform::UpdateWorld()
{
    S = XMMatrixScaling(lScale.x, lScale.y, 1.0f);
    R = XMMatrixRotationRollPitchYaw(lRotation.x, lRotation.y, lRotation.z);
    T = XMMatrixTranslation(lTranslation.x, lTranslation.y, 0.0f);

    P = XMMatrixTranslation(pivot.x, pivot.y, 0.0f);
    IP = XMMatrixInverse(nullptr, P); // ¿ªÇà·Ä

    world = IP * S * R * T * P;

    if (parent != nullptr)
        world *= parent->world;

    XMStoreFloat4x4(&fWorld, world);

    right = Vector2(fWorld._11, fWorld._12).Normal();
       up = Vector2(fWorld._21, fWorld._22).Normal();

    XMVECTOR outS, outR, outT;
    XMMatrixDecompose(&outS, &outR, &outT, world);

    XMStoreFloat2(&gScale, outS);
    XMStoreFloat2(&gPosition, outT);
}

void Transform::Debug()
{
    if (ImGui::BeginMenu(label.c_str()))
    {
        ImGui::DragFloat2("Position", (float*)&lTranslation, 1.0f, 0.0f, WIN_WIDTH);
        ImGui::DragFloat2("Scale", (float*)&lScale, 0.1f, 0.1f, 50.0f);
        ImGui::SliderAngle("Angle", &lRotation.z);
        ImGui::EndMenu();
    }
}
