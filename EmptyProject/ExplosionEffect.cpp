#include "DXUT.h"
#include "ExplosionEffect.h"


ExplosionEffect::ExplosionEffect()
{
}


ExplosionEffect::~ExplosionEffect()
{
}

void ExplosionEffect::Update()
{
	if (fElapsed >= fDelay)
	{
		fElapsed = 0.f;
		
		if (iCount < veTexs.size() - 1)
			iCount++;
		else
			bDestroy = true;
	
		lpBBRenderer->lpEffectTex = veTexs[iCount];
	}
	else
		fElapsed += Et;
	
}

void ExplosionEffect::SetExplosion(RefStr keys, int min, int max, float fS)
{
	AC(BBRenderer);
	LoadTexs(veTexs, keys, min, max);
	fDelay = fS;
	lpBBRenderer->lpEffectTex = veTexs[0];
	
}
