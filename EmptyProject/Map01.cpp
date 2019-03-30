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
	AC(Renderer);
	lpRenderer->lpMesh = GetMesh_(L"Stage01");
}
