#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	vBuffer = new MatrixBuffer;
}

Camera::~Camera()
{
	delete vBuffer;
}

void Camera::Update()
{
	if (target == nullptr) // point라 nullptr로 처리하지만 !target로 처리해도 똑같다.
		FreeMode();
	else
		TargetMode();

	UpdateWorld();

	Matrix view = XMMatrixInverse(nullptr, world);

	vBuffer->Set(view); // world를 넘기는게 아닌 view를 넘긴다고 생각해야한다, 위에 view 역행렬 생성후 입력

	vBuffer->SetVSBuffer(1);
}

void Camera::FreeMode()
{
	if (KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_PRESS('A'))
			lTranslation += V_LEFT * speed * Time::Delta();

		if (KEY_PRESS('D'))
			lTranslation += V_RIGHT * speed * Time::Delta();

		if (KEY_PRESS('S'))
			lTranslation += V_DOWN * speed * Time::Delta();

		if (KEY_PRESS('W'))
			lTranslation += V_UP * speed * Time::Delta();
	}
}

void Camera::TargetMode()
{
	Vector2 destination = target->GlobalPosition() - offset; // 선형보간 적용

	lTranslation = Vector2::Lerp(lTranslation, destination, Time::Delta());	// 속도의 비례해서 이동
}

