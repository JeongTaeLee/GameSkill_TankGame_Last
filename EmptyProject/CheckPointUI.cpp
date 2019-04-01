#include "DXUT.h"
#include "CheckPointUI.h"


CheckPointUI::CheckPointUI()
{
}


CheckPointUI::~CheckPointUI()
{
}

void CheckPointUI::Init()
{
	transform->vPos = Vector3(WINDOWX / 2.f, WINDOWY / 2.f, 0.f);
	transform->vScale = Vector3(0.f, 0.f, 0.f);

	AC(UIRenderer);
	lpUIRenderer->lpTex = GetTex(L"CheckPoint");
	lpUIRenderer->vCenterPos = Vector3(lpUIRenderer->lpTex->info.Width / 2.f, lpUIRenderer->lpTex->info.Height / 2.f, 0.f);
}

void CheckPointUI::Update()
{
	D3DXVec3Lerp(&transform->vScale, &transform->vScale, &Vector3(1.f, 1.f, 1.f), 0.2f);
	
	if (1.f <= fElapsed)
	{
		fElapsed = 0.f;
		bDestroy = true;
	}
	else
		fElapsed += Et();
}
