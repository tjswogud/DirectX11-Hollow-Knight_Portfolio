#pragma once

/*
Design Pattern(������ ����) : �ý����� �����ϴ� ���

Singleton Pattern(�̱��� ����) :

�ν��Ͻ��� static ������ ����ϴ� ���

*/

#define MAX_KEY 256

typedef unsigned char byte;

enum KeyState
{
	NONE,
	DOWN,
	UP,
	PRESS
};

class Keyboard
{
private:
	Keyboard();
	~Keyboard();

public:
	static void Create();
	static void Delete();

	static Keyboard* Get();

	void Update();

	bool  Down(DWORD key) { return keyMap[key] == DOWN; }
	bool    Up(DWORD key) { return keyMap[key] == UP; }
	bool Press(DWORD key) { return keyMap[key] == PRESS; }

private:
	static Keyboard* instance;

	byte keyState[MAX_KEY];
	byte keyOldState[MAX_KEY];
	byte keyMap[MAX_KEY];
};
