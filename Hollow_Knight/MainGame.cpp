#include "Framework.h"
#include "MainGame.h"

MainGame::MainGame()
{
    Environment::Get();

        Time::Create();
    Keyboard::Create();

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(DEVICE, DC);

    SkillManager::Get();

    //scene = new TutorialScene;
    //scene = new WorldScene;
    //scene = new SolarScene;
    //scene = new TextureScene;
    //scene = new CollisionScene;
    //scene = new AnimationScene;
    scene = new HollowScene;
}

MainGame::~MainGame()
{
    Environment::Delete();

        Time::Delete();
    Keyboard::Delete();

    EffectManager::Delete();

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();

    ImGui::DestroyContext();

    SkillManager::Delete();

    delete scene;
}

void MainGame::Update()
{
        Time::Get()->Update();
    Keyboard::Get()->Update();

    CAMERA->Update();
    EFFECT->Update();

    scene->Update();

    // 2740 438
   /* if (true)
    {
        if (KEY_DOWN(VK_UP))
        {
            delete scene;
            
            scene = new MapScene;
        }
    }*/
}

void MainGame::Render()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();


    string str = "FPS : " + to_string(Time::Get()->GetFPS());
    ImGui::Text(str.c_str());


    str = "MousePos : " + to_string((int)mousePos.x) + ", " + to_string((int)mousePos.y);
    ImGui::Text(str.c_str());

    scene->Render();
    EFFECT->Render();
    ImGui::Render();

    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
