#include "DXUT.h"
#include "PlayerDieEffect.h"
#include "Explosion3D.h"

PlayerDieEffect::PlayerDieEffect()
{
}


PlayerDieEffect::~PlayerDieEffect()
{
}

void PlayerDieEffect::Update()
{
	if (fElapsd >= fDelay)
	{
		fElapsd = 0.f;

		if (iCount < 10)
		{
			float fRandom = GetRandomNumber(-25.f, 25.f);
			Vector3 vPos(fRandom, fRandom, 0.f);
			CreateExplosionB(transform->vPos + Vector3(fRandom, fRandom, 0.f));
		}
		else
		{
			bDestroy = true;
			return;
		}


		if (iCount == 7)
		{
			switch (eType)
			{
			case e_tank01:
				AddObject(Explosion3D)->Set3DExplosion(transform->vPos, Vector3(0.3f, 0.3f, 0.3f), L"PlayerADie%d", 0, 20, 0.05f);
				break;
			case e_tank02:
				AddObject(Explosion3D)->Set3DExplosion(transform->vPos, Vector3(0.3f, 0.3f, 0.3f), L"PlayerBDie%d", 0, 20, 0.05f);
				break;
			case e_tank03:
				AddObject(Explosion3D)->Set3DExplosion(transform->vPos, Vector3(0.3f, 0.3f, 0.3f), L"PlayerCDie%d", 0, 20, 0.05f);
				break;
			default:
				break;
			}
		}

		iCount++;
	}
	else
		fElapsd += Et();
}

void PlayerDieEffect::SetPlayerDieEffect(PLAYERTYPE _eType, RefV3 vPos)
{
	transform->vPos = vPos;
	eType = _eType;
}
