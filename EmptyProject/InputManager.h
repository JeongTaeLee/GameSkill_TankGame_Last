#pragma once
#include "singleton.h"
class InputManager :
	public singleton < InputManager> 
{
public:
	bool bNowKey[256];
	bool bOldKey[256];
public:
	InputManager();
	virtual ~InputManager();

	void Update();

	Vector2 GetMPos();

	bool KeyDown(int i) { return bNowKey[i] && !bOldKey[i]; }
	bool KeyPress(int i) { return bNowKey[i] && bOldKey[i]; }
	bool KeyUp (int i) { return !bNowKey[i] && bOldKey[i]; }

};

#define INPUT InputManager::Getinst()

#define KEYDOWN(i) INPUT->KeyDown(i)
#define KEYUP(i) INPUT->KeyUp(i)
#define KEYPRESS(i) INPUT->KeyPress(i)