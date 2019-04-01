#include "DXUT.h"
#include "Stage01.h"

#include "MonsterSpawn.h"
#include "PlayerTank.h"
#include "Ranking.h"

Stage01::Stage01()
{
}


Stage01::~Stage01()
{
}

void Stage01::Init()
{
	SOUND->Play(L"Ingame", true);

	PlayerTank * tank = AddObject(PlayerTank);

	MAP->lpTank = tank;
	MAP->LoadStage01();

	MonsterSpawn * lpSpawn = AddObject(MonsterSpawn);
	lpSpawn->lpPlayer = tank;

	SOUND->DuplicatePlay(L"Start");
}

void Stage01::Release()
{
	SOUND->Stop(L"Ingame");

	OBJECT->Reset();
}

void Stage01::Update()
{
}
