#include "DXUT.h"
#include "Map.h"


Map::Map()
{
}


Map::~Map()
{
}

void Map::Init()
{
	AC(ShaderRenderer);
	lpShaderRenderer->lpEffect = GetEffect(L"Lighting");
}
