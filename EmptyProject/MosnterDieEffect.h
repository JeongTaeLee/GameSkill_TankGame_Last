#pragma once
#include "GameObject.h"
#include "Monster.h"

class MosnterDieEffect :
	public GameObject
{
public:
	MONSTERTYPE eType;
	
	int iCount = 0;
	
	float fElapsd = 0.f;
	float fDelay = 0.05f;
public:
	MosnterDieEffect();
	virtual ~MosnterDieEffect();

	virtual void Update()	override;

	void SetMonsterDieEffect(MONSTERTYPE _eType, RefV3 vPos, RefV3 vScale = Vector3(0.5f, 0.5f, 0.5f));

};

