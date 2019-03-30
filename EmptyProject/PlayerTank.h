#pragma once
#include "GameObject.h"

enum PLAYERSTATE
{
	E_PLAYERSTATE_DIE,
	E_PLAYERSTATE_SPAWN,
	E_PLAYERSTATE_IDLE,
};

enum PLAYERMOVETYPE
{
	E_MOVE_NONE,
	E_MOVE_BACK,
	E_MOVE_FORWARD,
};

class PlayerTank :
	public GameObject
{
public:
	PLAYERSTATE eState = E_PLAYERSTATE_IDLE;
	PLAYERMOVETYPE eMoveType = E_MOVE_NONE;

	Camera * lpCamera = nullptr;
	Quaternion qCameraRot;
	
	bool bMove = false;

	float fShakeElapsed = 0.f;
	float fShakeDelay = 0.1f;

	Vector3 vLookDir = Vector3(0.f, 0.f, 0.f);
public:
	PlayerTank();
	virtual ~PlayerTank();

	virtual void Init()	override;
	virtual void Release() override;
	virtual void Update() override;

public:
	void Idle();

	void CameraSetting();
};

