#include "DXUT.h"
#include "MapManager.h"
#include "Map01.h"
#include "PlayerTank.h"
#include "SkyBox.h"
#include "CheckPoint.h"
#include "Stone.h"
#include "Map02.h"

bool ScoreSotring(pair<wstring, int> & s1, pair<wstring, int> & s2)
{
	return s1.second > s2.second;
}


MapManager::MapManager()
{
}


MapManager::~MapManager()
{
}

void MapManager::ResetMap()
{
	lpMap = nullptr;

	vHeightMap.clear();

	iWidth = 0;

	vWidthMap.clear();
	iWidthIndex = 0;
}

void MapManager::LoadStage01()
{
	ResetMap();

	AddObject(SkyBox);
	lpMap = AddObject(Map01);
	lpMap->transform->vScale.z = -1.f;
	lpMap->transform->vPos = Vector3(20.f, 25.f, 0.f);
	
	SetHieghtMap(GetTex(L"Stage01Height"));
	SetWidthMap(GetTex(L"Stage01Width"));
	lpTank->vSpawnPos = lpTank->transform->vPos = Vector3(vWidthMap[0].x, vHeightMap[0].second, vWidthMap[0].z);
}

void MapManager::LoadStaga02()
{
	ResetMap();

	AddObject(SkyBox);
	lpMap = AddObject(Map02);
	lpMap->transform->vScale.z = -1.f;
	lpMap->transform->vPos = Vector3(22.f, 35.f, 0.f);

	SetHieghtMap(GetTex(L"Stage02Height"));
	SetWidthMap(GetTex(L"Stage02Width"));
	lpTank->vSpawnPos = lpTank->transform->vPos = Vector3(vWidthMap[0].x, vHeightMap[0].second, vWidthMap[0].z);
}

void MapManager::SetWidthMap(texture * lpWidthMap)
{
	int iWidth = lpWidthMap->info.Width;
	int iHeight = lpWidthMap->info.Height;

	D3DLOCKED_RECT locked;
	lpWidthMap->lpTex->LockRect(0, &locked, nullptr, D3DLOCK_DISCARD);

	DWORD * pColor = (DWORD*)locked.pBits;

	bool bFirst = false;

	for (int x = 0; x < iWidth; ++x)
	{
		for (int z = 0; z < iHeight; ++z)
		{
			D3DXCOLOR color = pColor[(iWidth * z) + x];

			if (color == D3DXCOLOR(0.f, 1.f, 0.f, 1.f))
			{
				CheckPoint * check = AddObject(CheckPoint);
				check->transform->vPos = Vector3(x, vHeightMap[x].second, (z - (float)iHeight / 2.f) * -1);
				check->lpPlayer = lpTank;

				vWidthMap.push_back(Vector3(x, vHeightMap[x].second, (z - (float)iHeight / 2.f) * -1));
				
				if (!bFirst)
				{
					check->bPass = true;
					bFirst = true;
				}
			}

			if (color == D3DXCOLOR(0.f, 0.f, 1.f, 1.f))
			{
				Stone * lpStone = AddObject(Stone);
				lpStone->lpPlayer = lpTank;
				lpStone->transform->vPos = Vector3(x, vHeightMap[x].second, (z - (float)iHeight / 2.f) * -1);
			}
		}
	}
	lpWidthMap->lpTex->UnlockRect(0);

}

void MapManager::SetHieghtMap(texture * lpHeightMap)
{
	iWidth = lpHeightMap->info.Width;
	int iHeight = lpHeightMap->info.Height;

	D3DLOCKED_RECT rect;

	lpHeightMap->lpTex->LockRect(0, &rect, nullptr, D3DLOCK_DISCARD);
	DWORD * pColor = (DWORD*)rect.pBits;

	for (int x = 0; x < iWidth; ++x)
	{
		for (int y = 0; y < iHeight; ++y)
		{
			D3DXCOLOR color = D3DXCOLOR(pColor[(iWidth * y) + x]);

			if (color == D3DXCOLOR(1.f, 0.f, 1.f, 1.f))
			{
				vHeightMap.push_back(make_pair(e_magenta, iHeight - y));
				break;
			}
			if (color == D3DXCOLOR(1.f, 0.f, 0.f, 1.f))
			{
				vHeightMap.push_back(make_pair(e_red, iHeight - y));
				break;
			}
		}
	}
	lpHeightMap->lpTex->UnlockRect(0);
}

int MapManager::GetBastScore()
{
	if(liScores.size() != 0)
		return liScores[0].second;

	return 0;
}

void MapManager::SaveScore(wstring strName, int iScore)
{
	for (auto Iter = liScores.begin(); Iter != liScores.end();)
	{
		if (Iter->first == strName)
			Iter = liScores.erase(Iter);
		else
			++Iter;
	}

	liScores.push_back(make_pair(strName, iScore));

	sort(liScores.begin(), liScores.end(), ScoreSotring);

	wofstream output(L"./rs/score.txt", ios::trunc);

	for (auto Iter : liScores)
		output << Iter.first << " " <<Iter.second;

	output.close();
}

void MapManager::LoadScore()
{
	wifstream input(L"./rs/score.txt");

	if (input.fail())
	{
		DEBUG_LOG("ScoreData Load Failed!");
		return;
	}
	while (!input.eof()) {
		wstring str;
		int score = 0;

		input >> str >> score;
		liScores.push_back(make_pair(str, score));
	}

	input.close();
}
