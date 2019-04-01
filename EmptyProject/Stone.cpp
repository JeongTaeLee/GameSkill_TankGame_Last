#include "DXUT.h"
#include "Stone.h"
#include "LockOnCrossHair.h"

Stone::Stone()
{
	sTag = "Stone";
}


Stone::~Stone()
{
}

void Stone::Init()
{
	transform->vScale = Vector3(0.3f, 0.3f, 0.3f);

	lpLockOnCrossHair = AddObject(LockOnCrossHair);
	lpLockOnCrossHair->lpTarget = this;

	AC(ShaderRenderer);
	lpShaderRenderer->lpEffect = GetEffect(L"Lighting");

	AC(Animater);
	lpAnimater->Add(L"Stone", L"Stone%d", 0, 20, [&]() {bDestroy = true; });
	lpAnimater->Chanage(L"Stone", 0.05f);
	lpAnimater->Stop(0);

	AC(Collider);
	lpCollider->SetCollider(20.f, Vector3(0.f, 0.f, 0.f));
}

void Stone::Release()
{
	lpLockOnCrossHair->bDestroy = true;
}

void Stone::Update()
{
	if (bHit)
	{
		bHit = false;
		transform->vPos.x += 10;
	}
}

void Stone::ReceiveCollider(Collider * lpOther)
{
	if (bExplosion)
		return;

	if (lpOther->gameObject->sTag == "PlayerBullet" || lpOther->gameObject->sTag == "Player")
	{
		bHit = true;
		transform->vPos.x -= 10;

		iLife--;
		DEBUG_LOG(iLife);

		if (iLife <= 0)
		{
			bExplosion = true;
			lpCollider->bEnable = false;
			lpAnimater->UnStop();
		}
	}
}
