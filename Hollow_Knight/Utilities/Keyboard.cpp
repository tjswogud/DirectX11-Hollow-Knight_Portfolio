#include "Framework.h"
#include "Keyboard.h"

Keyboard* Keyboard::instance = nullptr;

Keyboard::Keyboard()
{
	/*
	�迭,����ü�� �ʱ�ȭ �ϴ� ���
	
	1. ���� ����� = {};
	2. ZeroMemory
	3. memset

	*/ 

	//memset(keyState, 0, sizeof(keyState));
	ZeroMemory(keyState,    sizeof(keyState));
	ZeroMemory(keyOldState, sizeof(keyOldState));
	ZeroMemory(keyMap,      sizeof(keyMap));

}

Keyboard::~Keyboard()
{
}

void Keyboard::Create()
{
	if (instance == nullptr)
		instance = new Keyboard;
}

void Keyboard::Delete()
{
	if (instance != nullptr)
		delete instance;
}

Keyboard* Keyboard::Get()
{
	return instance;
}

void Keyboard::Update()
{
	memcpy(keyOldState, keyState, sizeof(keyState));

	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyMap,   sizeof(keyMap));

	//   0,   1 : Ű���带 ������ ���� ����
	// 128, 129 : Ű���带 ���� ����
	GetKeyboardState(keyState);

	for (int i = 0; i < MAX_KEY; i++)
	{
		byte key = keyState[i] & 0x80;
		keyState[i] = key ? 1 : 0;

		byte old = keyOldState[i];
		byte cur = keyState[i];

		if (old == 0 && cur == 1)      //���� 0, ���� 1 : DOWN
			keyMap[i] = DOWN;
		else if (old == 1 && cur == 0) //���� 1, ���� 0 : UP
			keyMap[i] = UP;
		else if (old == 1 && cur == 1) //���� 1, ���� 1 : PRESS
			keyMap[i] = PRESS;
		else
			keyMap[i] = NONE;
	}
}

