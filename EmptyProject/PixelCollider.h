#pragma once
#include "Component.h"
class PixelCollider :
	public Component
{
public:
	Vector3 vLeft = Vector3(0.f, 0.f, 0.f);
	Vector3 vRight = Vector3(0.f, 0.f, 0.f);
	int iHeight = 0;


	PIXELTYPE eCallType = e_none;
	function<void()> funcMagenta = nullptr;
	function<void()> funcRed = nullptr;
public:
	PixelCollider();
	virtual ~PixelCollider();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update()	override;

public:
	bool  CheckHeight(Vector3 & vPos);
};

