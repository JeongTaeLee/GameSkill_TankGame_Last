#pragma once
#include "GameObject.h"
#include "PlayerTank.h"

class PlayerDieEffect :
	public GameObject
{
public:
	PLAYERTYPE eType;
	int iCount = 0;

	float fElapsd = 0.f;
	float fDelay = 0.05f;
public:
	PlayerDieEffect();
	virtual ~PlayerDieEffect();

	virtual void Update()	override;
	void SetPlayerDieEffect(PLAYERTYPE _eType, RefV3 vPos);


};

