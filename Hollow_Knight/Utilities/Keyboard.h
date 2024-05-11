#pragma once

/*
Design Pattern(디자인 패턴) : 시스템을 설계하는 방식

Singleton Pattern(싱글톤 패턴) :

인스턴스를 static 변수로 사용하는 방식

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
