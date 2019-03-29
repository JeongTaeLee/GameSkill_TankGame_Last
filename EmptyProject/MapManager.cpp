#include "DXUT.h"
#include "MapManager.h"
#include "Map01.h"
#include "PlayerTank.h"
MapManager::MapManager()
{
}


MapManager::~MapManager()
{
}

void MapManager::ResetMap()
{
	SAFE_DELETE_ARRAY(lpMap);
}

void MapManager::LoadStage01()
{
	lpMap = AddObject(Map01);
	lpMap->transform->vScale.z = -1.f;
	//lpMap->transform->vPos = Vector3(50.f, 0.f, 0.f);
	
	SetWidthMap(GetTex(L"TestMapWidth"));
	lpTank->transform->vPos = Vector3(vWidthMap[0].x, 0.f, vWidthMap[0].z);
}

void MapManager::LoadStaga02()
{
}

void MapManager::SetWidthMap(texture * lpWidthMap)
{
	int iWidth = lpWidthMap->info.Width;
	int iHeight = lpWidthMap->info.Height;

	D3DLOCKED_RECT locked;
	lpWidthMap->lpTex->LockRect(0, &locked, nullptr, D3DLOCK_DISCARD);

	DWORD * pColor = (DWORD*)locked.pBits;

	for (int x = 0; x < iWidth; ++x)
	{
		for (int z = 0; z < iHeight; ++z)
		{
			D3DXCOLOR color = pColor[(iWidth * z) + x];

			if (color == D3DXCOLOR(0.f, 1.f, 0.f, 1.f))
				vWidthMap.push_back(Vector3(x, 0.f, (z - (float)iHeight / 2.f) * -1));
		}
	}
}

void MapManager::SetHieghtMap(texture * lpHeightMap)
{
}
