#include "DXUT.h"
#include "SkyBox.h"


SkyBox::SkyBox()
{
}


SkyBox::~SkyBox()
{
}

void SkyBox::Init()
{
	AC(Renderer);
	lpRenderer->lpMesh = GetMesh_(L"Stage01SkyBox");
}

void SkyBox::Update()
{
	transform->vPos = CAMERA->GetCamera()->vPos;
}
