#pragma once
#include "GameObject.h"
class ExplosionEffect :
	public GameObject

{
public:
	vector<texture*> veTexs;

	int iCount = 0;

	float fElapsed = 0.f;
	float fDelay = 0.f;

	function < void() > func;
public:
	ExplosionEffect();
	virtual ~ExplosionEffect();

	virtual void Update()	override;

	void SetExplosion(RefStr keys, int min , int max, float fS);

};

