#include "DXUT.h"
#include "Screen.h"


Screen::Screen()
{
}


Screen::~Screen()
{
}

void Screen::Update()
{
	if (KEYUP(VK_ESCAPE))
		bDestroy = true;
}

void Screen::SetScreen(texture * lpScreen)
{
	AC(UIRenderer);
	lpUIRenderer->lpTex = lpScreen;
	transform->vPos = Vector3(319, 107, 0.f);
}
