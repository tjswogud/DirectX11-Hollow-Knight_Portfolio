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
	if (target == nullptr) // point�� nullptr�� ó�������� !target�� ó���ص� �Ȱ���.
		FreeMode();
	else
		TargetMode();

	UpdateWorld();

	Matrix view = XMMatrixInverse(nullptr, world);

	vBuffer->Set(view); // world�� �ѱ�°� �ƴ� view�� �ѱ�ٰ� �����ؾ��Ѵ�, ���� view ����� ������ �Է�

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
	Vector2 destination = target->GlobalPosition() - offset; // �������� ����

	lTranslation = Vector2::Lerp(lTranslation, destination, Time::Delta());	// �ӵ��� ����ؼ� �̵�
}

