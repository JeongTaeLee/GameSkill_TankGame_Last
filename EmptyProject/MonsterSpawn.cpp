#include "DXUT.h"
#include "MonsterSpawn.h"
#include "PlayerTank.h"

#include "MonsterA.h"
#include "MonsterB.h"
int MonsterSpawn::iMonsterCount = 0;


MonsterSpawn::MonsterSpawn()
{
}


MonsterSpawn::~MonsterSpawn()
{
}

void MonsterSpawn::Update()
{
	if (lpPlayer)
	{
		if (lpPlayer->bDestroy)
		{
			lpPlayer = nullptr;
			return;
		}
	}
	else
		return;

	if (iMonsterCount < 3)
	{
		if (fCreateElapsed >= fCreateDelay)
		{
			fCreateElapsed = 0.f;
			iMonsterCount += 2;

			MonsterA * lpMonster = AddObject(MonsterA);
			lpMonster->lpPlayer = lpPlayer;

			MonsterB * lpMonsterB = AddObject(MonsterB);
			lpMonsterB->lpPlayer = lpPlayer;

			Vector3 vCreatePos = lpPlayer->transform->vPos +
				Vector3(300.f, 250.f, 0.f);

			Vector3 vCreatePos02 = lpPlayer->transform->vPos +
				Vector3(-300.f, 250.f, 0.f);

			if (SCENE->sName == L"Stage01")
			{
				lpMonsterB->SetMonsterB(MONSTERTYPE::E_MONSTERTYPE_B1, vCreatePos02, Vector3(300.f, 250.f, 0.f));
				lpMonster->SetMonsterA(MONSTERTYPE::E_MONSTERTYPE_A1, vCreatePos, Vector3(300.f, 250.f, 0.f));
			}
			else if (SCENE->sName == L"Stage02")
			{
				lpMonsterB->SetMonsterB(MONSTERTYPE::E_MONSTERTYPE_B2, vCreatePos02, Vector3(300.f, 250.f, 0.f));
				lpMonster->SetMonsterA(MONSTERTYPE::E_MONSTERTYPE_A2, vCreatePos, Vector3(300.f, 250.f, 0.f));
			}
		}
		else
			fCreateElapsed += Et();
	}
}
