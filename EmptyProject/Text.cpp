#include "DXUT.h"
#include "Text.h"


Text::Text()
{
}


Text::~Text()
{
}

void Text::Init()
{
	gameObject->lpText = this;
	
	OBJECT->AddUIRenderer(this);
}

void Text::Release()
{
	if (gameObject->lpText == this)
		gameObject->lpText = nullptr;

	OBJECT->DeleteUIRenderer(this);
}

void Text::Render()
{
	if (str != L"None")
	{
		LPD3DXFONT lpFont = nullptr;
		D3DXCreateFont(g_device, iSize, 0, FW_ULTRABOLD, 1, false,
			DEFAULT_CHARSET, D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, L"¸¼Àº °íµñ", &lpFont);

		RECT re = { 0 };

		Matrix matPos;
		D3DXMatrixTranslation(&matPos, vPos.x, vPos.y, 0.f);
		matPos = transform->matWorld * matPos;

		RESOURCE->lpSprite->SetTransform(&matPos);
		lpFont->DrawTextW(RESOURCE->lpSprite, str.c_str(), -1, &re, DT_NOCLIP, color);

		SAFE_RELEASE(lpFont);
	}
}
