#pragma once
#include "GameObject.h"

enum MONSTERASTATE
{
	E_IDLE,
	E_ATTACK,
	E_LAST,
};



enum MONSTERTYPE
{
	E_MONSTERTYPE_A1,
	E_MONSTERTYPE_A2,
	E_MONSTERTYPE_B1,
	E_MONSTERTYPE_B2,
};

class PlayerTank;
class LockOnCrossHair;

class Monster :
	public GameObject
{
public:
	PlayerTank * lpPlayer = nullptr;
	LockOnCrossHair * lpLockOnHair = nullptr;
	
	MONSTERTYPE eMonsterType = E_MONSTERTYPE_A1;

	int iLife = 0;
public:
	Monster();
	virtual ~Monster();

	virtual void Init()	override;
	virtual void Release()	override;
	void HommingCheck();

	void CreateItem();


	virtual void ReceiveCollider(Collider * lpOther) override;
};

