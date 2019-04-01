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

	if(SCENE->sName == L"Stage01")
		lpRenderer->lpMesh = GetMesh_(L"Stage01SkyBox");
	if (SCENE->sName == L"Stage02")
		lpRenderer->lpMesh = GetMesh_(L"Stage02SkyBox");
}

void SkyBox::Update()
{
	transform->vPos = CAMERA->GetCamera()->vPos;
}
