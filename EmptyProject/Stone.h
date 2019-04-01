#pragma once
#include "GameObject.h"

class PlayerTank;
class LockOnCrossHair;

class Stone :
	public GameObject
{
public:
	PlayerTank * lpPlayer = nullptr;
	LockOnCrossHair * lpLockOnCrossHair = nullptr;
	
	int iLife = 5;

	bool bExplosion = false;
	bool bHit = false;
public:
	Stone();
	virtual ~Stone();

	virtual void Init()	override;
	virtual void Release()	override;
	virtual void Update()	override;


	virtual void ReceiveCollider(Collider * lpOther);
};

