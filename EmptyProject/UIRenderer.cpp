#include "DXUT.h"
#include "UIRenderer.h"


UIRenderer::UIRenderer()
{
}


UIRenderer::~UIRenderer()
{
}

void UIRenderer::Init()
{
	gameObject->lpUIRenderer = this;
	gameObject->transform->eType = TU_3;
	OBJECT->AddUIRenderer(this);
}

void UIRenderer::Release()
{
	if (gameObject->lpUIRenderer == this)
		gameObject->lpUIRenderer = nullptr;

	OBJECT->DeleteUIRenderer(this);
}

void UIRenderer::Render()
{
	if (lpTex)
	{
		Matrix matPos;
		D3DXMatrixTranslation(&matPos, vPos.x, vPos.y, 0.f);
		matPos = transform->matWorld * matPos;

		RESOURCE->lpSprite->SetTransform(&matPos);
		RESOURCE->lpSprite->Draw(lpTex->lpTex, nullptr, &vCenterPos, nullptr, color);
	}
}
