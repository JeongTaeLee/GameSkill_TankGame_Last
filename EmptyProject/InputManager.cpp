#include "DXUT.h"
#include "InputManager.h"


InputManager::InputManager()
{
	memset(bNowKey, false, sizeof(bool) * 256);
	memset(bOldKey, false, sizeof(bool) * 256);

}


InputManager::~InputManager()
{
}

void InputManager::Update()
{
	memcpy(bOldKey, bNowKey, sizeof(bool) * 256);
	memset(bNowKey, false, sizeof(bool) * 256);

	for (int i = 0; i < 256; ++i)
		bNowKey[i] = GetAsyncKeyState(i);
}

int InputManager::GetInputKey()
{
	for (int i = 65; i < 91; ++i)
	{
		if (bNowKey[i] && !bOldKey[i])
			return i;
	}
	return -1;
}

Vector2 InputManager::GetMPos()
{
	POINT pt = { 0 };
	GetCursorPos(&pt);
	ScreenToClient(DXUTGetHWND(), &pt);

	return Vector2(pt.x, pt.y);
}
