#include "DXUT.h"
#include "MonsterSpawn.h"
#include "PlayerTank.h"

#include "MonsterA.h"
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
			iMonsterCount++;
			DEBUG_LOG(iMonsterCount);
			
			MonsterA * lpMonster = AddObject(MonsterA);
			lpMonster->lpPlayer = lpPlayer;
			
			Vector3 vCreatePos = lpPlayer->transform->vPos +
				Vector3(300.f, 250.f, 0.f);

			if (SCENE->sName == L"Stage01")
				lpMonster->SetMonsterA(MONSTERTYPE::E_MONSTERTYPE_1, vCreatePos, Vector3(300.f, 250.f, 0.f));
			else if (SCENE->sName == L"Stage02")
				lpMonster->SetMonsterA(MONSTERTYPE::E_MONSTERTYPE_2, vCreatePos, Vector3(300.f, 250.f, 0.f));
		}
		else
			fCreateElapsed += Et;
	}
}
