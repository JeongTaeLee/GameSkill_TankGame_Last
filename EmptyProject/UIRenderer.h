#pragma once
#include "Component.h"
class UIRenderer :
	public Component
{
public:
	texture * lpTex = nullptr;

	D3DXCOLOR color = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	Vector3 vCenterPos = Vector3(0.f, 0.f, 0.f);
public:
	UIRenderer();
	virtual ~UIRenderer();

	virtual void Init()	override;
	virtual void Release()	override;

	virtual void Render()	override;
};

