#pragma once
#include "GameObject.h"

class Explosion3D :
	public GameObject
{
public:
	float fDelay = 0.f;
	float fElapsed = 0.f;
public:
	Explosion3D();
	virtual ~Explosion3D();

	virtual void Set3DExplosion(RefV3 vPos, RefV3 vScale, RefStr keys, int min, int max, float fS);

};

