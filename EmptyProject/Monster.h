#pragma once
#include "GameObject.h"

enum MONSTERTYPE
{
	E_MONSTERTYPE_1,
	E_MONSTERTYPE_2,
};

class PlayerTank;
class LockOnCrossHair;

class Monster :
	public GameObject
{
public:
	PlayerTank * lpPlayer = nullptr;
	LockOnCrossHair * lpLockOnHair = nullptr;

	int iLife = 0;
public:
	Monster();
	virtual ~Monster();

	virtual void Init()	override;
	virtual void Release()	override;



	virtual void ReceiveCollider(Collider * lpOther) override;
};

