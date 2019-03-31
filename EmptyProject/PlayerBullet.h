#pragma once
#include "GameObject.h"

enum PLAYERBULLETYPE
{
	E_PLAYERBULLET_01,
	E_PLAYERBULLET_02,
};


class PlayerBullet :
	public GameObject
{
public:
	Vector3 vDir = Vector3(0.f, 0.f, 1.f);

	float fPower = 0.f;

	float fDelay = 0.f;
	float fElapsed = 0.f;
public:
	PlayerBullet();
	virtual ~PlayerBullet();

	virtual void Init()	override;
	virtual void Update()	override;

	void SetBullet(PLAYERBULLETYPE type, RefV3 vPos, Quaternion qRot, float fPower, float fTime);

	virtual void ReceiveCollider(Collider * lpOther) override;

};

