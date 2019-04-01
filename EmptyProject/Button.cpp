#include "DXUT.h"
#include "Button.h"


Button::Button()
{
}


Button::~Button()
{
}

void Button::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(DXUTGetHWND(), &pt);

	if (PtInRect(&reRect, pt))
	{
		D3DXVec3Lerp(&transform->vScale, &transform->vScale, &Vector3(1.2f, 1.2f, 1.2f), 0.2f);

		float fColor = lpUIRenderer->color;
		
		if (fColor > 0.5f)
			lpUIRenderer->color.r = lpUIRenderer->color.g = lpUIRenderer->color.b = fColor - 0.1f;

		if (KEYUP(VK_LBUTTON))
		{
			SOUND->DuplicatePlay(L"Click");
			if (func)
				func();
		}
	}
	else
	{
		D3DXVec3Lerp(&transform->vScale, &transform->vScale, &Vector3(1.0f, 1.0f, 1.0f), 0.2f);
		lpUIRenderer->color.r = lpUIRenderer->color.g = lpUIRenderer->color.b = 1.f;
	}
}

void Button::SetButton(texture * lpButtonTexture, RefV3 vPos, int Width, int Height)
{
	transform->vPos = vPos;

	AC(UIRenderer);
	lpUIRenderer->lpTex = lpButtonTexture;
	lpUIRenderer->vCenterPos = Vector3(lpUIRenderer->lpTex->info.Width / 2.f,
		lpUIRenderer->lpTex->info.Height / 2.f, 0.f);

	SetRect(&reRect, vPos.x - Width / 2.f, vPos.y - Height / 2.f, vPos.x + Width / 2.f, vPos.y + Height / 2.f);
}
