#pragma once
#include "GameObject.h"

enum PLAYERSTATE
{
	E_PLAYERSTATE_DIE,
	E_PLAYERSTATE_SPAWN,
	E_PLAYERSTATE_IDLE,
};

class PlayerTank :
	public GameObject
{
public:
	PLAYERSTATE eState = E_PLAYERSTATE_IDLE;

	Camera * lpCamera = nullptr;
	Vector3 vLookDir = Vector3(0.f, 0.f, 0.f);

	bool bMove = false;
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

