#include "DXUT.h"
#include "Stage01.h"

#include "MonsterSpawn.h"
#include "PlayerTank.h"

Stage01::Stage01()
{
}


Stage01::~Stage01()
{
}

void Stage01::Init()
{
	PlayerTank * tank = AddObject(PlayerTank);

	MAP->lpTank = tank;
	MAP->LoadStage01();

	MonsterSpawn * lpSpawn = AddObject(MonsterSpawn);
	lpSpawn->lpPlayer = tank;
}

void Stage01::Release()
{
	OBJECT->Reset();
}

void Stage01::Update()
{
}
