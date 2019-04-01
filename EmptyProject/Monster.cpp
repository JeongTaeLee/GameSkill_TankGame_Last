#include "DXUT.h"
#include "Monster.h"
#include "MonsterSpawn.h"
#include "LockOnCrossHair.h"
#include "MosnterDieEffect.h"
#include "Item.h"
Monster::Monster()
{
	sTag = "Monster";
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

void Monster::CreateItem()
{
	ITEMTYPE item = (ITEMTYPE)GetRandomNumber((int)ITEMTYPE::ITEM_D, (int)ITEMTYPE::ITEM_U);

	AddObject(Item)->SetItem(transform->vPos, item);
}

void Monster::ReceiveCollider(Collider * lpOther)
{
	if (bDestroy)
		return;


	if (lpOther->gameObject->sTag == "NuClear")
	{
		iLife = 0;

		if (iLife <= 0)
		{
			AddObject(MosnterDieEffect)->SetMonsterDieEffect(eMonsterType, transform->vPos, Vector3(0.2f, 0.2f, 0.2f));
			CreateItem();
			bDestroy = true;
		}
	}

	if (lpOther->gameObject->sTag == "PlayerBullet")
	{
		--iLife;

		if (iLife <= 0)
		{
			AddObject(MosnterDieEffect)->SetMonsterDieEffect(eMonsterType, transform->vPos, Vector3(0.2f, 0.2f, 0.2f));
			CreateItem();
			bDestroy = true;
		}
	}
}
