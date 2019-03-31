#include "DXUT.h"
#include "LockOnCrossHair.h"


LockOnCrossHair::LockOnCrossHair()
{
}


LockOnCrossHair::~LockOnCrossHair()
{
}

void LockOnCrossHair::Init()
{
	AC(UIRenderer);
	lpUIRenderer->lpTex = GetTex(L"LockOnCrossHair");
	lpUIRenderer->vCenterPos = Vector3(lpUIRenderer->lpTex->info.Width / 2.f, lpUIRenderer->lpTex->info.Height / 2.f, 0.f);
}

void LockOnCrossHair::Update()
{
	if (lpTarget)
	{
		if (lpTarget->bDestroy)
		{
			lpTarget = nullptr;
			return;
		}
	
		Vector3 v2Dpos;
		WorldTo2D(v2Dpos, lpTarget->transform->vPos);
		transform->vPos = v2Dpos;
	}
	else return;
}
