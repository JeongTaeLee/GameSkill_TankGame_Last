#include "DXUT.h"
#include "Collider.h"
#include "DebugCollider.h"

Collider::Collider()
{
}


Collider::~Collider()
{
}

void Collider::Init()
{
	gameObject->lpCollider = this;

	OBJECT->AddCollider(this);
}

void Collider::Release()
{
	if (gameObject->lpCollider == this)
		gameObject->lpCollider = nullptr;

	OBJECT->DeleteCollider(this);
}

void Collider::SetCollider(float _fRad, const Vector3 & _vOffset)
{
	gameObject->AC(DebugCollider)->SetDebugCollider(_fRad);

	fRad = _fRad;
	vOffset = _vOffset;
}

Vector3 Collider::GetOffset()
{
	Vector3 vNowOffset = Vector3(0.f, 0.f, 0.f);

	Matrix matRot = transform->matRot;
	memcpy(&matRot._41, &transform->vWorldPos, sizeof(Vector3));

	D3DXVec3TransformCoord(&vNowOffset, &vOffset, &matRot);
	return vNowOffset;
}

void Collider::OnCollider(Collider * _lpCollider)
{
	gameObject->SendCollider(_lpCollider);
}
