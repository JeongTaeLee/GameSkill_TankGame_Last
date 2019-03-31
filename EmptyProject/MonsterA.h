#pragma once
#include "Monster.h"

enum MONSTERASTATE
{
	E_IDLE,
	E_ATTACK,
	E_LAST,
};


class MonsterA :
	public Monster
{
public:
	float fElapsed = 0.f;
	float fDelay = 0.5f;

	Vector3 vOffset = Vector3(0.f, 0.f, 0.f);

	function< void() > funcState[E_LAST];
	MONSTERASTATE eState;

	Vector3 vDir = Vector3(0.f, 0.f, 0.f);
public:
	MonsterA();
	virtual ~MonsterA();

	virtual void Init()	override;
	virtual void Update()	override;

	void OnAttack();
	void OnIdle();

	void SetMonsterA(MONSTERTYPE eType, RefV3 _vPos, RefV3 _vOffset);

};

