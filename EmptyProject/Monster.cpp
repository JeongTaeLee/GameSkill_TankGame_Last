#include "DXUT.h"
#include "Monster.h"
#include "MonsterSpawn.h"
#include "LockOnCrossHair.h"
#include "MosnterDieEffect.h"
#include "Item.h"
#include "PlayerTank.h"
#include "PlayerUI.h"

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

void Monster::HommingCheck()
{
	if (lpPlayer->eWeapon == PLAYERWEAPON::e_homming)
		lpLockOnHair->lpUIRenderer->bEnable = true;
	else
		lpLockOnHair->lpUIRenderer->bEnable = false;


	Vector3 v2Dpos = Vector3(0.f, 0.f, 0.f);
	WorldTo2D(v2Dpos, transform->vPos);

	Vector2 vMousePos = INPUT->GetMPos();
	float fLegnth = GetLength(Vector3(vMousePos.x, vMousePos.y, 0.f), v2Dpos);

	if (fLegnth < 50.f)
	{
		if (KEYDOWN(VK_LBUTTON))
			lpPlayer->FireHommingMissile(this);
	}
}

void Monster::CreateItem()
{
	int fRandom = GetRandomNumber(0, 100);

	if (fRandom < 50.f)
	{
		ITEMTYPE item = (ITEMTYPE)GetRandomNumber((int)ITEMTYPE::ITEM_D, (int)ITEMTYPE::ITEM_U);
		Item * item_ = AddObject(Item);
		item_->SetItem(transform->vPos, item);
		item_->lpTank = lpPlayer;
	}
}

void Monster::ReceiveCollider(Collider * lpOther)
{
	if (bDestroy)
		return;

	if (lpOther->gameObject->sTag == "NuClear" || lpOther->gameObject->sTag == "Homming")
	{
		iLife = 0;

		if (iLife <= 0)
		{
			lpPlayer->lpPlayerUI->AddScore(100);

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
			lpPlayer->lpPlayerUI->AddScore(100);

			AddObject(MosnterDieEffect)->SetMonsterDieEffect(eMonsterType, transform->vPos, Vector3(0.2f, 0.2f, 0.2f));
			CreateItem();
			bDestroy = true;
		}
	}
}
