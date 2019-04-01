#pragma once
#include "GameObject.h"
class PlayerNuClear :
	public GameObject
{
public:
	Camera * lpCamera = nullptr;

	bool bExplsion = false;
	float fElapsed = 0.f;
	float fDelay = 1.f;
public:
	PlayerNuClear();
	virtual ~PlayerNuClear();

	virtual void Init()	override;
	virtual void Update()	override;

};

