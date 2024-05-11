#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
    //rects.emplace_back(new Rect(Vector2(-0.5f, -0.5f), Vector2(0.2f, 0.2f)));
    //rects.emplace_back(new Rect(Vector2(+0.5f, +0.5f), Vector2(0.2f, 0.2f)));
    
    rects.emplace_back(new Object(Vector2(0, 0), Vector2(100, 100)));

    wBuffer = new MatrixBuffer;    

    // 주 대각선 1로 다 초기화 단위행렬 만들어줌

    wMatrix._11 = 1;
    wMatrix._22 = 1;
    wMatrix._33 = 1;
    wMatrix._44 = 1;

    wMatrix2._11 = 1;
    wMatrix2._22 = 1;
    wMatrix2._33 = 1;
    wMatrix2._44 = 1;
}

TutorialScene::~TutorialScene()
{
    for (Object * rect : rects)
        delete rect;

    rects.clear();

    delete wBuffer;
    
}

void TutorialScene::Update()
{
    wMatrix._41 = mousePos.x;
    wMatrix._42 = mousePos.y;

    if (KEY_PRESS('A'))
    {
        wMatrix2._41 -= Time::Delta() * 100;
    }
    if (KEY_PRESS('D'))
    {
        wMatrix2._41 += Time::Delta() * 100;
    }
    if (KEY_PRESS('S'))
    {
        wMatrix2._42 -= Time::Delta() * 100;
    }
    if (KEY_PRESS('W'))
    {
        wMatrix2._42 += Time::Delta() * 100;
    }

}

void TutorialScene::Render()
{
    Matrix temp = XMLoadFloat4x4(&wMatrix);

    wBuffer->Set(temp);

    wBuffer->SetVSBuffer(0);
    

    for (Object * rect : rects)
        rect->Render();

    //////////////////////////////////

    temp = XMLoadFloat4x4(&wMatrix2);

    wBuffer->Set(temp);

    wBuffer->SetVSBuffer(0);

    for (Object* rect : rects)
        rect->Render();
}


