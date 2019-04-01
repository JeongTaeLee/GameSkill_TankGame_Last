#include "DXUT.h"
#include "ItemUI.h"


ItemUI::ItemUI()
{
}


ItemUI::~ItemUI()
{
}

void ItemUI::Update()
{
	if (fElapsed > fDelay) {
		fElapsed = 0.f;
		bDestroy = true;
	}
	else
		fElapsed += Et();

	D3DXVec3Lerp(&transform->vScale, &transform->vScale, &Vector3(1.f, 1.f, 1.f), 0.2f);
}

void ItemUI::SetItemUI(ITEMTYPE eItemType)
{
	AC(UIRenderer);
	switch (eItemType)
	{
	case ITEM_D:
		lpUIRenderer->lpTex = GetTex(L"Display_D");
		break;
	case ITEM_H:
		lpUIRenderer->lpTex = GetTex(L"Display_H");
		break;
	case ITEM_M:
		lpUIRenderer->lpTex = GetTex(L"Display_M");
		break;
	case ITEM_N:
		lpUIRenderer->lpTex = GetTex(L"Display_N");
		break;
	case ITEM_R:
		lpUIRenderer->lpTex = GetTex(L"Display_R");
		break;
	case ITEM_S:
		lpUIRenderer->lpTex = GetTex(L"Display_S");
		break;
	case ITEM_U:
		lpUIRenderer->lpTex = GetTex(L"Display_U");
		break;
	default:
		break;
	}

	lpUIRenderer->vCenterPos =
		Vector3(lpUIRenderer->lpTex->info.Width / 2.f, lpUIRenderer->lpTex->info.Height / 2.f, 0.f);

	transform->vPos = Vector3((float)WINDOWX / 2.f, (float)WINDOWY / 2.f - 100.f, 0.f);
	transform->vScale = Vector3(0.f, 0.f, 0.f);
}
