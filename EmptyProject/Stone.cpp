#include "DXUT.h"
#include "Stone.h"
#include "LockOnCrossHair.h"
#include "PlayerTank.h"
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
	if (lpPlayer)
	{
		if (lpPlayer->bDestroy)
		{
			lpPlayer = nullptr;
			return;
		}

		Vector3 v2Dpos;
		WorldTo2D(v2Dpos, transform->vPos);

		//30.f;
		Vector2 vMousePos = INPUT->GetMPos();
		float fLegnth = GetLength(Vector3(vMousePos.x, vMousePos.y, 0.f), v2Dpos);

		if (fLegnth < 30.f)
			lpPlayer->FireHommingMissile(this);
	}
	else
		return;

}

void Stone::ReceiveCollider(Collider * lpOther)
{
	if (bExplosion)
		return;

	if (lpOther->gameObject->sTag == "NuClear" || lpOther->gameObject->sTag == "Homming")
	{
		iLife = 0;

		if (iLife <= 0)
		{
			bExplosion = true;
			lpCollider->bEnable = false;
			lpAnimater->UnStop();
		}
	}


	if (lpOther->gameObject->sTag == "PlayerBullet" || lpOther->gameObject->sTag == "Player")
	{
		iLife--;

		if (iLife <= 0)
		{
			bExplosion = true;
			lpCollider->bEnable = false;
			lpAnimater->UnStop();
		}
	}
}
