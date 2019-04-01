#include "DXUT.h"
#include "PlayerNuClear.h"


PlayerNuClear::PlayerNuClear()
{
	sTag = "NuClear";
}


PlayerNuClear::~PlayerNuClear()
{
}

void PlayerNuClear::Init()
{
	lpCamera = CAMERA->GetCamera(L"NuClearCamera");
	CAMERA->ChanageCamera(L"NuClearCamera");

	transform->vScale = Vector3(0.5f, 0.5f, 0.5f);

	AC(ShaderRenderer);
	lpShaderRenderer->lpEffect = GetEffect(L"Lighting");
	lpShaderRenderer->lpMesh = GetMesh_(L"NuClear");

	AC(RigidBody);
	lpRigidBody->bUseGravity = true;
	lpRigidBody->fMass = 1.f;

	AC(Collider);
	lpCollider->SetCollider(300.f, Vector3(0.f, 0.f, 0.f));
	lpCollider->bEnable = false;

	AC(PixelCollider);
	lpPixelCollider->funcCall = [&]() {
		if (!bExplsion)
		{
			SOUND->DuplicatePlay(L"Explosion");
			bExplsion = true;
			lpCollider->bEnable = true;
			lpRenderer->bEnable = false;
			CAMERA->SetShake(10.f, 1.5f);
		}
	};
}

void PlayerNuClear::Update()
{
	if (bExplsion) {		
		Vector3 vTarget = transform->vPos + Vector3(0.f, 100.f, -350.f);
		D3DXVec3Lerp(&lpCamera->vPos, &lpCamera->vPos, &vTarget, 0.2f);
		D3DXVec3Lerp(&lpCamera->vLookAt, &lpCamera->vLookAt, &transform->vPos, 0.2f);
		

		if (fElapsed >= fDelay)
		{
			bDestroy = true;
			fElapsed = 0.f;
		}
		else
			fElapsed += Et();
	}
	else
	{
		Vector3 vTarget = transform->vPos + Vector3(0.f, 50.f, -200.f);
		D3DXVec3Lerp(&lpCamera->vPos, &lpCamera->vPos, &vTarget, 0.2f);
		D3DXVec3Lerp(&lpCamera->vLookAt, &lpCamera->vLookAt, &transform->vPos, 0.2f);
	}
}
