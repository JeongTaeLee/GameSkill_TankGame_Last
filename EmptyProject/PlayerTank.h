#pragma once
#include "GameObject.h"

enum PLAYERSTATE
{
	E_PLAYERSTATE_DIE,
	E_PLAYERSTATE_SPAWN,
	E_PLAYERSTATE_IDLE,
	E_PLAYERSTATE_NUCLEAR,
};

enum PLAYERTYPE
{
	e_noneTankType ,
	e_tank01,
	e_tank02,
	e_tank03,
};

enum PLAYERWEAPON
{
	e_base,
	e_homming,
	e_nuclear,
};

class PlayerGun;
class PlayerUI;

class PlayerTank :
	public GameObject
{
public:
	PLAYERSTATE eState = E_PLAYERSTATE_IDLE;
	PLAYERTYPE eType = e_noneTankType;
	
	PLAYERWEAPON eWeapon = e_base;
	Vector3 vWeaponFirePos = Vector3(0.f, 0.f, 0.f);

	PlayerUI * lpPlayerUI = nullptr;;

	Camera * lpCamera = nullptr;
	Camera * lpNuClearCamera = nullptr;

	Quaternion qCameraRot;
	Vector3 vRight = Vector3(0.f, 0.f, 0.f);

	PlayerGun * lpGun;

	int iLife = 3;

	
	bool bGameEnd = false;
	bool bLifeInfinity = false;
	bool bBack = false;
	bool bMove = false;
	bool bOnFloor = false;
	bool bDoubleJump = false;

	float fTotalSpeed = 0.f;

	float fShakeElapsed = 0.f;
	float fShakeDelay = 0.1f;

	float fSpawnDelay = 2.f;
	float fSpawnElapsed = 0.f;



	Vector3 vLookDir = Vector3(0.f, 0.f, 0.f);
public:
	int iHommingCount = 5;
	
	int iNuClearCount = 2;
	float fNuClearDelay = 5.f;
	float fNuClearElapsed = 0.f;

	bool bDoubleJumpEnable = false;
	float fDoubleJumpElapsed = 0.f;
	float fDoubleJumpDelay = 20.f;

	bool bNwayBulletEnable = false;
	float fNwayBulletDelay = 20.f;
	float fNwayBulletElapsed = 0.f;

	bool bRangeUpEnable = false;
	float fRangeUpDelay = 10.f;
	float fRangeUpElapsed = 0.f;

	bool bSpeedUpEnable = false;
public:
	PlayerTank();
	virtual ~PlayerTank();

	virtual void Init()	override;
	virtual void Release() override;
	virtual void Update() override;

	virtual void ReceiveCollider(Collider * lpOther) override;

public:
	void Idle();
	void Spawn();
	void Attack();

	void SetTank(PLAYERTYPE etype);
	void SetState(PLAYERSTATE _eState);
	void ItemTimeCheck();

	void CameraSetting();

	static Vector3 vSpawnPos;

public:
	void SetDoubleJump();
	void SetSpeedUp();
	void SetUpgrad();
	void SetRangeUp();
	void SetNwayBullet();
	void AddNuClear();
	void AddHomming();

	void FireHommingMissile(GameObject * lpTank);
};

