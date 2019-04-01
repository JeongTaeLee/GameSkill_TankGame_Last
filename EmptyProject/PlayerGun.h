#pragma once
#include "GameObject.h"

enum PLAYERGUNTYPE
{
	e_noneGunType,
	e_gun01,
	e_gun02,
	e_gun03,
};

class PlayerGun :
	public GameObject
{
public:
	PLAYERGUNTYPE eGunType = e_noneGunType;

	CMeshLoader * lpA = nullptr;
	CMeshLoader * lpB = nullptr;
	CMeshLoader * lpC = nullptr;
public:
	PlayerGun();
	virtual ~PlayerGun();

	virtual void Init()	override;
	virtual void Update()	override;

	void Attack(RefV3 vRight, bool _bNwayBullet);

	void SetGun(PLAYERGUNTYPE _eGunType);

};

