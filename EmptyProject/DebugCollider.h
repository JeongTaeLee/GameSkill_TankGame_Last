#pragma once
#include "Component.h"
class DebugCollider :
	public Renderer
{
public:
	LPD3DXMESH lpSphere = nullptr;
public:
	DebugCollider();
	virtual ~DebugCollider();

	virtual void Init()	override;
	virtual void Release()override;
	virtual void Update()	override;
	virtual void Render()	override;

	void SetDebugCollider(float fRad);
};

