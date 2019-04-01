#include "DXUT.h"
#include "RigidBody.h"

static Vector3 vGravity = Vector3(0.f, -9.8f, 0.f);

RigidBody::RigidBody()
{
}


RigidBody::~RigidBody()
{
}

void RigidBody::Init()
{
	gameObject->lpRigidBody = this;
}

void RigidBody::Release()
{
	if (gameObject->lpRigidBody == this)
		gameObject->lpRigidBody = nullptr;
}

void RigidBody::Update()
{
	if (bUseGravity)
		vForce += vGravity * fMass;

	vVelocity += vForce;
	vForce = Vector3(0.f, 0.f, 0.f);

	vDir = transform->vPos;
	transform->vPos += vVelocity * Et();
	vDir = transform->vPos - vDir;
	D3DXVec3Normalize(&vDir, &vDir);

	vVelocity.x *= vDecrease.x;
	vVelocity.y *= vDecrease.y;
	vVelocity.z *= vDecrease.z;
}
