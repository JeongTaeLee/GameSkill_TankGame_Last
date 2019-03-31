#pragma once
#include "GameObject.h"
class LockOnCrossHair :
	public GameObject
{
public:
	GameObject * lpTarget = nullptr;
public:
	LockOnCrossHair();
	virtual ~LockOnCrossHair();

	virtual void Init()	override;
	virtual void Update()	override;
};

