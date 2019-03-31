#include "DXUT.h"
#include "Monster.h"
#include "MonsterSpawn.h"
#include "LockOnCrossHair.h"

Monster::Monster()
{
}


Monster::~Monster()
{
	--MonsterSpawn::iMonsterCount;
}

void Monster::Init()
{
	lpLockOnHair = AddObject(LockOnCrossHair);
	lpLockOnHair->lpTarget = this;
}

void Monster::Release()
{
	if (lpLockOnHair)
		lpLockOnHair->bDestroy = true;
}

void Monster::ReceiveCollider(Collider * lpOther)
{
	if (lpOther->gameObject->sTag == "PlayerBullet")
	{
		--iLife;

		if (iLife <= 0)
			bDestroy = true;
	}
}
