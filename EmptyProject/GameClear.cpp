#include "DXUT.h"
#include "GameClear.h"
#include "Button.h"

GameClear::GameClear()
{
}


GameClear::~GameClear()
{
}

void GameClear::Init()
{
	transform->vPos = Vector3(WINDOWX / 2.f, WINDOWY / 2.f, 0.f);
	transform->vScale = Vector3(0.f, 0.f, 1.f);

	AC(UIRenderer);
	lpUIRenderer->lpTex = GetTex(L"GameClear");
	lpUIRenderer->vCenterPos = Vector3(lpUIRenderer->lpTex->info.Width / 2.f, lpUIRenderer->lpTex->info.Height / 2.f, 0.f);

	fFrameTime = 0.f;
}

void GameClear::Update()
{
	if (!bCompleteProcess)
	{
		Vector3 vScale = Vector3(1.f, 1.f, 1.f);
		D3DXVec3Lerp(&transform->vScale, &transform->vScale, &Vector3(1.f, 1.f, 1.f), 0.3f);

		float fLength = GetLength(transform->vScale, vScale);

		if (fLength < 0.01f)
		{
			bCompleteProcess = true;
			transform->vScale = Vector3(1.f, 1.f, 1.f);

			if(SCENE->sName == L"Stage01")
			{
				Button * button = AddObject(Button);
				button->SetButton(GetTex(L"NextStageButton"), Vector3(640.f, 630.5f, 0.f), 223, 55);
				button->func = [&]() { SCENE->ChangeScene(L"Stage02"); fFrameTime = 1.f; };
			}
			else 
			{
				Button * button = AddObject(Button);
				button->SetButton(GetTex(L"MainButton"), Vector3(640.f, 630.5f, 0.f), 223, 55);
				button->func = [&]() { SCENE->ChangeScene(L"VictoryScene"); fFrameTime = 1.f; };
			}
		}
	}
}
