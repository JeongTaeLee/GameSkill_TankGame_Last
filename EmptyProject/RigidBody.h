#pragma once
#include "Component.h"
class RigidBody :
	public Component
{
public:
	Vector3 vVelocity = Vector3(0.f, 0.f, 0.f);
	Vector3 vForce = Vector3(0.f, 0.f, 0.f);
	Vector3 vDecrease = Vector3(0.98f, 0.98f, 0.98f);
	Vector3 vDir = Vector3(0.f, 0.f, 0.f);

	float fMass = 0.f;
	bool bUseGravity = false;
public:
	RigidBody();
	virtual ~RigidBody();	

	virtual void Init()	override;
	virtual void Release()	override;

	virtual void Update()	override;
public:
	void AddForce(RefV3 _fForce) { vForce += _fForce; }
};

