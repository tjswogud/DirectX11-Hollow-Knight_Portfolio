#include "Framework.h"
#include "Plane.h"

Plane::Plane()
	:Object(L"airplane.png")
{
	lTranslation = WIN_CENTER;
	
	pivot = Vector2(-100, -100);
}

Plane::~Plane()
{
}

void Plane::Update()
{
	UpdateWorld();

	Move();
}

void Plane::Render()
{
	SetColorBuffer(color);

	ImGui::ColorEdit4("Color", (float*)&color); // Vector4라서 형변환 해서 넣어줘야한다

	Object::Render();
}

void Plane::Move()
{
	if (KEY_PRESS('W'))
		lTranslation += up * 100 * Time::Delta();

	if (KEY_PRESS('S'))
		lTranslation -= up * 100 * Time::Delta();

	if (KEY_PRESS(VK_LEFT))
		lRotation.z += Time::Delta();

	if (KEY_PRESS(VK_RIGHT))
		lRotation.z -= Time::Delta();
}

