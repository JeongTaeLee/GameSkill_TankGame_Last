#include "DXUT.h"
#include "Stone.h"
#include "LockOnCrossHair.h"

Stone::Stone()
{
}


Stone::~Stone()
{
}

void Stone::Init()
{
	lpLockOnCrossHair = AddObject(LockOnCrossHair);
	lpLockOnCrossHair->lpTarget = this;

	AC(ShaderRenderer);
	lpShaderRenderer->lpEffect = GetEffect(L"Lighting");

	AC(Animater);
	lpAnimater->Add(L"Stone", L"Stone%d", 0, 20, [&]() {bDestroy = true; });
	lpAnimater->Chanage(L"Stone", 0.1f);
	lpAnimater->Stop(0);

	AC(Collider);
	lpCollider->SetCollider(30.f, Vector3(0.f, 0.f, 0.f));
}

void Stone::Release()
{
	lpLockOnCrossHair->bDestroy = true;
}

void Stone::Update()
{
}

void Stone::ReceiveCollider(Collider * lpOther)
{
	if (bExplosion)
		return;

	if (lpOther->gameObject->sTag == "PlayerBullet" || lpOther->gameObject->sTag == "Player")
	{
		lpCollider->bEnable = false;
		
		bExplosion = true;
		lpAnimater->UnStop();
	}
}
