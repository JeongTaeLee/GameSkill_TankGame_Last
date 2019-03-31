#include "DXUT.h"
#include "Map01.h"


Map01::Map01()
{
}


Map01::~Map01()
{
}

void Map01::Init()
{
	Map::Init();
	lpRenderer->lpMesh = GetMesh_(L"Stage01");
}
