#include "DXUT.h"
#include "Map02.h"


Map02::Map02()
{
}


Map02::~Map02()
{
}

void Map02::Init()
{
	Map::Init();
	lpRenderer->lpMesh = GetMesh_(L"Stage02");
}
