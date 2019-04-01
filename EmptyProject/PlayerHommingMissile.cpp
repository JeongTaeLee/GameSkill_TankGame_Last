#include "DXUT.h"
#include "PlayerHommingMissile.h"


PlayerHommingMissile::PlayerHommingMissile()
{
	sTag = "Homming";
}


PlayerHommingMissile::~PlayerHommingMissile()
{
}

void PlayerHommingMissile::Init()
{
	transform->eType = TU_2;

	transform->vScale = Vector3(0.3f, 0.3f, 0.3f);

	AC(ShaderRenderer);
	lpShaderRenderer->lpEffect = GetEffect(L"Lighting");
	DEBUG_LOG("in");
	lpShaderRenderer->lpMesh = GetMesh_(L"HommingMissile");

	AC(Collider);
	lpCollider->SetCollider(10.f, Vector3(0.f, 0.f, 0.f));
}

void PlayerHommingMissile::Update()
{
	if (lpTarget)
	{
		if (lpTarget->bDestroy)
		{
			bDestroy = true;
			CreateExplosionA(transform->vPos);
			return;
		}

		Vector3 vDir = lpTarget->transform->vPos - transform->vPos;
		D3DXVec3Normalize(&vDir, &vDir);

		transform->vPos += vDir * (700 * Et());
		
		GetLookAtS(transform->qRot, vDir, 0.2f);
	}
	else
	{
		bDestroy = true;
		CreateExplosionA(transform->vPos);
	}
}

void PlayerHommingMissile::SetHomming(RefV3 vPos, GameObject * _lpTarget)
{
	transform->vPos = vPos;
	lpTarget = _lpTarget;
}

void PlayerHommingMissile::ReceiveCollider(Collider * lpOther)
{
	if (lpOther->gameObject->sTag == "Monster" || lpOther->gameObject->sTag == "Stone")
	{
		SOUND->DuplicatePlay(L"Explosion");

		CreateExplosionA(transform->vPos);
		bDestroy = true;
		CAMERA->SetShake(2.f, 0.5f);
	}
}
