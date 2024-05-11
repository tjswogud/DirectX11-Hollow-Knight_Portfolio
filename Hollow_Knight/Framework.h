#pragma once

#include "__Others/targetver.h"
#define WIN32_LEAN_AND_MEAN  
#include <windows.h>
#include <string>
#include <map>
#include <vector>
#include <functional>

using namespace std;

#define WIN_WIDTH 1540
#define WIN_HEIGHT 1000

#define WIN_CENTER_X WIN_WIDTH  * 0.5f
#define WIN_CENTER_Y WIN_HEIGHT * 0.5f

#define WIN_CENTER Vector2(WIN_CENTER_X, WIN_CENTER_Y)


#define DEVICE Device::Get()->GetDevice()
#define DC     Device::Get()->GetDC()

#define KEY_PRESS(p) Keyboard::Get()->Press(p)
#define KEY_DOWN(p)  Keyboard::Get()->Down(p)
#define KEY_UP(p)    Keyboard::Get()->Up(p)

#define CAMERA Environment::Get()->GetCamera()
#define EFFECT EffectManager::Get()

#define MAP_CHANGE Vector2(2740, 438)

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

using namespace DirectX;

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_dx11.h>
#include <ImGui/imgui_impl_win32.h>

#pragma comment(lib, "ImGui/ImGui.lib")

#include <DirectXTex/DirectXTex.h>

#pragma comment(lib, "DirectXTex/DirectXTex.lib")

//typedef XMFLOAT2 Vector2;
typedef XMFLOAT3 Vector3;
typedef XMFLOAT4 Vector4;
typedef XMMATRIX Matrix;

#include "Objects/Vector2.h"
#include "Objects/Transform.h"

#include "Utilities/Singleton.h"
#include "Utilities/Keyboard.h"
#include "Utilities/Time.h"
#include "Utilities/Math.h"

using namespace Math;

#include "Systems/Device.h"

#include "Renders/Buffers/VertexLayouts.h"
#include "Renders/Buffers/VertexBuffer.h"
#include "Renders/Buffers/IndexBuffer.h"
#include "Renders/Buffers/ConstantBuffer.h"
#include "Renders/Buffers/GlobalBuffer.h"

#include "Renders/Shaders/VertexShader.h"
#include "Renders/Shaders/PixelShader.h"

#include "Renders/Texture/Texture.h"
#include "Renders/Texture/Frame.h"
#include "Renders/Texture/Animation.h"

#include "Objects/Basic/Object.h"
#include "Objects/Basic/Polygons.h"

#include "Objects/Effect/Effect.h"
#include "Objects/Effect/EffectManager.h"

#include "Collision/Collider.h"
#include "Collision/ColliderRect.h"
#include "Collision/ColliderCircle.h"

#include "GameObject/Character.h"
#include "GameObject/Battle/Mario.h"

#include "GameObject/SolarSystem/Planet.h"
#include "GameObject/Plane/Plane.h"

#include "Environment/Camera.h"
#include "Environment/Environment.h"

// Hollow Knight
#include "Hollow_Knight/Skill.h"
#include "Hollow_Knight/SkillManager.h"
#include "Hollow_Knight/AttackSlash.h"
#include "Hollow_Knight/Map.h"
#include "Hollow_Knight/Knight.h"
#include "Hollow_Knight/Boss.h"
#include "Hollow_Knight/Enemy.h"
#include "Hollow_Knight/EnemyManager.h"

#include "Scenes/Scene.h"
#include "Scenes/TutorialScene.h"
#include "Scenes/WorldScene.h"
#include "Scenes/SolarScene.h"
#include "Scenes/TextureScene.h"
#include "Scenes/CollisionScene.h"
#include "Scenes/AnimationScene.h"
#include "Scenes/HollowScene.h"
#include "Scenes/MapScene.h"

#include "MainGame.h"

extern HWND hWnd;
extern Vector2 mousePos;