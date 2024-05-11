#include "Framework.h"
#include "WorldScene.h"

WorldScene::WorldScene()
    :scale(1.0f, 1.0f), rotation(0.0f), translation(0.0f, 0.0f), angle(0)
{
    rect = new Object(Vector2(0, 0), Vector2(100, 100));

    wBuffer = new MatrixBuffer;

    identity._11 = 1;
    identity._22 = 1;
    identity._33 = 1;
    identity._44 = 1;

        /*S = identity; // 전부 단위행렬로 초기화 한 과정
        R = identity;
        T = identity;*/

         S = XMMatrixIdentity();
         R = XMMatrixIdentity();
         T = XMMatrixIdentity();
    world  = XMMatrixIdentity();
    world2 = XMMatrixIdentity();
}

WorldScene::~WorldScene()
{
    delete rect;
    delete wBuffer;
}

void WorldScene::Update()
{
    ////Scale
    //if (KEY_PRESS(VK_RIGHT))
    //    S._11 += 0.01f;
    //if (KEY_PRESS(VK_LEFT))
    //    S._11 -= 0.01f;

    //if (KEY_PRESS(VK_UP))
    //    S._22 += 0.01f;
    //if (KEY_PRESS(VK_DOWN))
    //    S._22 -= 0.01f;

    ////Rotation
    //R._11 =  cos(rotation);
    //R._12 =  sin(rotation);
    //R._21 = -sin(rotation);
    //R._22 =  cos(rotation);

    //if (KEY_PRESS('Q'))
    //    rotation += Time::Delta();
    //if (KEY_PRESS('E'))
    //    rotation -= Time::Delta();

    ////Translation
    //if (KEY_PRESS('A'))
    //    T._41 -= Time::Delta() * 100;
    //if (KEY_PRESS('D'))
    //    T._41 += Time::Delta() * 100;
    //
    //if (KEY_PRESS('S'))
    //    T._42 -= Time::Delta() * 100;
    //if (KEY_PRESS('W'))
    //    T._42 += Time::Delta() * 100;

    //world = XMLoadFloat4x4(&S) * XMLoadFloat4x4(&R) * XMLoadFloat4x4(&T);

    S = XMMatrixScaling(scale.x, scale.y, 1.0f); // 결과값을 S로
    R = XMMatrixRotationZ(rotation);
    T = XMMatrixTranslation(translation.x, translation.y, 0.0f);

    world = S * R * T;

    // 아래 식 = 월드 행렬이 fWorld로 바뀐것
    XMFLOAT4X4 fWorld;
    XMStoreFloat4x4(&fWorld, world);

    right = { fWorld._11, fWorld._12 };
    up    = { fWorld._21, fWorld._22 };

    if (KEY_PRESS('W'))
    {
        translation.x += up.x;
        translation.y += up.y;
    }

    if (KEY_PRESS('S'))
    {
        translation.x -= up.x;
        translation.y -= up.y;
    }

    if (KEY_PRESS('D'))
    {
        translation.x += right.x;
        translation.y += right.y;
    }

    if (KEY_PRESS('A'))
    {
        translation.x -= right.x;
        translation.y -= right.y;
    }

    //
    angle += Time::Delta();

    Matrix R2 = XMMatrixRotationZ(angle);
    Matrix T2 = XMMatrixTranslation(100, 100, 0);
    world2 = R2 * T2;

    world *= world2;
}

void WorldScene::Render()
{
    wBuffer->Set(world);

    wBuffer->SetVSBuffer(0);

    rect->Render();

    /////////////////////

    wBuffer->Set(world2);

    wBuffer->SetVSBuffer(0);

    rect->Render();



    ImGui::SliderFloat2("Scale",       (float*)&scale,       0.0f, 5.0f);
    ImGui::SliderFloat ("Rotation",    (float*)&rotation,    0.0f, XM_2PI);
    ImGui::SliderFloat2("Translation", (float*)&translation, 0.0f, WIN_WIDTH);
}
