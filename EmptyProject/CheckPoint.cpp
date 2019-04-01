#include "DXUT.h"
#include "CheckPoint.h"
#include "PlayerTank.h"
#include "CheckPointUI.h"

CheckPoint::CheckPoint()
{
}


CheckPoint::~CheckPoint()
{
}

void CheckPoint::Init()
{
}

void CheckPoint::Update()
{
	if (!bPass)
	{
		if (transform->vPos.x <= lpPlayer->transform->vPos.x)
		{
			AddObject(CheckPointUI);
			PlayerTank::vSpawnPos = transform->vPos;
			bPass = true;
		}
	}

}
