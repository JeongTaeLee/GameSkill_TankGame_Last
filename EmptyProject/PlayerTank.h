#pragma once
#include "GameObject.h"

enum PLAYERSTATE
{
	E_PLAYERSTATE_DIE,
	E_PLAYERSTATE_SPAWN,
	E_PLAYERSTATE_IDLE,
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


class PlayerTank :
	public GameObject
{
public:
	PLAYERSTATE eState = E_PLAYERSTATE_IDLE;
	PLAYERTYPE eType = e_noneTankType;
	
	PLAYERWEAPON eWeapon = e_base;
	Vector3 vWeaponFirePos = Vector3(0.f, 0.f, 0.f);

	Camera * lpCamera = nullptr;
	Quaternion qCameraRot;

	PlayerGun * lpGun;

	int iLife = 3;

	bool bBack = false;
	bool bMove = false;
	bool bOnFloor = false;
	bool bDoubleJump = false;

	float fShakeElapsed = 0.f;
	float fShakeDelay = 0.1f;

	float fSpawnDelay = 2.f;
	float fSpawnElapsed = 0.f;

	Vector3 vLookDir = Vector3(0.f, 0.f, 0.f);

public:
	int iHommingCount = 0;
	int iNuClearCount = 0;


	float fDoubleJumpElapsed = 0.f;
	float fDoubleJumpDelay = 20.f;
	bool bDoubleJumpEnable = false;

	float fSpeedUpElapsed = 0.f;
	float fSpeedUpDelay = 20.f;
	bool bSpeedUpEnable = false;;

public:
	PlayerTank();
	virtual ~PlayerTank();

	virtual void Init()	override;
	virtual void Release() override;
	virtual void Update() override;
public:
	void Idle();
	void Spawn();
	void Attack();

	void SetTank(PLAYERTYPE etype);
	void SetState(PLAYERSTATE _eState);
	void ItemTimeCheck();

	
	void CameraSetting();

	static Vector3 vSpawnPos;
};

