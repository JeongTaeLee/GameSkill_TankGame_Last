#pragma once
#include "GameObject.h"

class PlayerTank;

class MonsterSpawn :
	public GameObject
{
public:
	PlayerTank  * lpPlayer = nullptr;

	float fCreateElapsed = 0.f;
	float fCreateDelay = 5.f;
public:
	MonsterSpawn();
	virtual ~MonsterSpawn();

	virtual void Update()	override;

	static int iMonsterCount;
};

