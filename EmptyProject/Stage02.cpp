#include "DXUT.h"
#include "Stage02.h"
#include "MonsterSpawn.h"
#include "PlayerTank.h"

Stage02::Stage02()
{
}


Stage02::~Stage02()
{
}

void Stage02::Init()
{
	SOUND->Play(L"Ingame", true);

	PlayerTank * tank = AddObject(PlayerTank);

	MAP->lpTank = tank;
	MAP->LoadStaga02();

	MonsterSpawn * lpSpawn = AddObject(MonsterSpawn);
	lpSpawn->lpPlayer = tank;

	SOUND->DuplicatePlay(L"Sound");
}

void Stage02::Release()
{
	SOUND->Stop(L"Ingame");
	OBJECT->Reset();
}

void Stage02::Update()
{
}
