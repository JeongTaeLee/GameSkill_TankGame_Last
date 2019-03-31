#pragma once
#include "GameObject.h"

class PlayerTank;

class CheckPoint :
	public GameObject
{
public:
	PlayerTank * lpPlayer = nullptr;

	bool bPass = false;
public:
	CheckPoint();
	virtual ~CheckPoint();

	virtual void Init()	override;
	virtual void Update()	override;
};

