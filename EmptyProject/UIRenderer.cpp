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
		RESOURCE->lpSprite->SetTransform(&transform->matWorld);
		RESOURCE->lpSprite->Draw(lpTex->lpTex, nullptr, &vCenterPos, nullptr, color);
	}
}
