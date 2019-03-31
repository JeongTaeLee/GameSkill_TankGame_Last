#include "DXUT.h"
#include "DebugCollider.h"


DebugCollider::DebugCollider()
{
}


DebugCollider::~DebugCollider()
{
}

void DebugCollider::Init()
{
	OBJECT->AddRenderer(this);
}

void DebugCollider::Release()
{
	SAFE_RELEASE(lpSphere);
	OBJECT->DeleteRenderer(this);

}

void DebugCollider::Update()
{
}

void DebugCollider::Render()
{
	if (lpSphere)
	{
		Vector3 vPos = gameObject->lpCollider->GetOffset();

		Matrix matWorld;
		D3DXMatrixTranslation(&matWorld, vPos.x, vPos.y, vPos.z);
	
		g_device->SetTransform(D3DTS_WORLD, &matWorld);
		g_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		g_device->SetTexture(0, nullptr);
		lpSphere->DrawSubset(0);

		g_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}

void DebugCollider::SetDebugCollider(float fRad)
{
	D3DXCreateSphere(g_device, fRad, 10, 10, &lpSphere, nullptr);
}
