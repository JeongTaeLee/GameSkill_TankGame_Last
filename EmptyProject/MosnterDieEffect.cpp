#include "DXUT.h"
#include "MosnterDieEffect.h"
#include "Explosion3D.h"

MosnterDieEffect::MosnterDieEffect()
{
}


MosnterDieEffect::~MosnterDieEffect()
{
}

void MosnterDieEffect::Update()
{
	if (fElapsd >= fDelay)
	{
		fElapsd = 0.f;

		if (iCount < 10)
		{
			float fRandom = GetRandomNumber(-10.f, 10.f);
			Vector3 vPos(fRandom, fRandom, 0.f);
			CreateExplosionB(transform->vPos + Vector3(fRandom, fRandom, 0.f));
		}
		else
			bDestroy = true;


		if (iCount == 7)
		{
			switch (eType)
			{
			case E_MONSTERTYPE_A1:
				AddObject(Explosion3D)->Set3DExplosion(transform->vPos, transform->vScale, L"MonsterA1Die%d", 0, 20, 0.05f);
				break;
			case E_MONSTERTYPE_A2:
				AddObject(Explosion3D)->Set3DExplosion(transform->vPos, transform->vScale, L"MonsterA2Die%d", 0, 20, 0.05f);
				break;
			case E_MONSTERTYPE_B1:
				AddObject(Explosion3D)->Set3DExplosion(transform->vPos, transform->vScale, L"MonsterB1Die%d", 0, 20, 0.05f);
				break;
			case E_MONSTERTYPE_B2:
				AddObject(Explosion3D)->Set3DExplosion(transform->vPos, transform->vScale, L"MonsterB2Die%d", 0, 20, 0.05f);
				break;
			}
		}
	
		iCount++;
	}
	else
		fElapsd += Et();
}

void MosnterDieEffect::SetMonsterDieEffect(MONSTERTYPE _eType, RefV3 vPos, RefV3 vScale)
{
	eType = _eType;
	transform->vPos = vPos;
	transform->vScale = vScale;
}
