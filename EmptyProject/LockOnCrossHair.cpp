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
	transform->vScale = Vector3(1.5f, 1.5f, 1.5f);
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
		
		//30.f;
		Vector2 vMousePos = INPUT->GetMPos();
		float fLegnth = GetLength(Vector3(vMousePos.x, vMousePos.y, 0.f), v2Dpos);

		if (fLegnth < 30.f)
		{
			lpUIRenderer->color = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
			D3DXVec3Lerp(&transform->vScale, &transform->vScale, &Vector3(2.f, 2.f, 2.f), 0.2f);
		}
		else
		{
			lpUIRenderer->color = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
			D3DXVec3Lerp(&transform->vScale, &transform->vScale, &Vector3(1.5f, 1.5f, 1.5f), 0.2f);
		}
	}
	else return;
}
