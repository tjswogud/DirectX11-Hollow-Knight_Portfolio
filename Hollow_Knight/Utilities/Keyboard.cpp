#include "Framework.h"
#include "Keyboard.h"

Keyboard* Keyboard::instance = nullptr;

Keyboard::Keyboard()
{
	/*
	배열,구조체를 초기화 하는 방법
	
	1. 변수 선언시 = {};
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

	//   0,   1 : 키보드를 누르지 않은 상태
	// 128, 129 : 키보드를 누른 상태
	GetKeyboardState(keyState);

	for (int i = 0; i < MAX_KEY; i++)
	{
		byte key = keyState[i] & 0x80;
		keyState[i] = key ? 1 : 0;

		byte old = keyOldState[i];
		byte cur = keyState[i];

		if (old == 0 && cur == 1)      //이전 0, 현재 1 : DOWN
			keyMap[i] = DOWN;
		else if (old == 1 && cur == 0) //이전 1, 현재 0 : UP
			keyMap[i] = UP;
		else if (old == 1 && cur == 1) //이전 1, 현재 1 : PRESS
			keyMap[i] = PRESS;
		else
			keyMap[i] = NONE;
	}
}

