#pragma once
#include "GameObject.h"
class MonsterBullet :
	public GameObject
{
public:
	Vector3 vDir = Vector3(0.f, 0.f, 0.f);

	float fPower = 0.f;
	float fElapsed = 0.f;
public:
	MonsterBullet();
	virtual ~MonsterBullet();

	virtual void Init()	override;
	virtual void Update()	override;

	void SetBullet(RefV3 vPos, RefV3 vDir, float fPower);
};

