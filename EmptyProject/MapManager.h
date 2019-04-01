#pragma once
#include "singleton.h"

enum PIXELTYPE
{
	e_none,
	e_red,
	e_magenta,
};

class Map;
class PlayerTank;

class MapManager :
	public singleton < MapManager >
{
public:
	Map * lpMap = nullptr;
	PlayerTank * lpTank = nullptr;

	vector<pair<PIXELTYPE, int> >	vHeightMap;
	int iWidth = 0;

	vector<Vector3> vWidthMap;
	int iWidthIndex = 0;
	
	int iScore = 0;
public:
	MapManager();
	virtual ~MapManager();

	void ResetMap();

	void LoadStage01();
	void LoadStaga02();

	void SetWidthMap(texture * lpWidthMap);
	void SetHieghtMap(texture * lpHeightMap);
};

#define MAP MapManager::Getinst()