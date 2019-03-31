#pragma once
#include "Component.h"
class Collider :
	public Component
{
public:
	Vector3 vOffset = Vector3(0.f, 0.f, 0.f);

	float fRad = 0.f;
public:
	Collider();
	virtual ~Collider();

	virtual void Init()	override;
	virtual void Release() override;

	void SetCollider(float fRad, const Vector3 & vOffset);

	Vector3 GetOffset();

public:
	void OnCollider(Collider * _lpCollider);
};

