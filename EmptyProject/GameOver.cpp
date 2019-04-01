#include "DXUT.h"
#include "GameOver.h"
#include "Button.h"

GameOver::GameOver()
{
}


GameOver::~GameOver()
{
}

void GameOver::Init()
{
	transform->vPos = Vector3(WINDOWX / 2.f, WINDOWY / 2.f, 0.f);
	transform->vScale = Vector3(0.f, 0.f, 1.f);

	AC(UIRenderer);
	lpUIRenderer->lpTex = GetTex(L"GameOver");
	lpUIRenderer->vCenterPos = Vector3(lpUIRenderer->lpTex->info.Width / 2.f, lpUIRenderer->lpTex->info.Height / 2.f, 0.f);

	fFrameTime = 0.f;
}

void GameOver::Update()
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

			Button * button = AddObject(Button);
			button->SetButton(GetTex(L"RetryButton"), Vector3(505.f, 609.f, 0.f), 223, 55);
			button->func = [&]() { SCENE->ChangeScene(L"LoseScene"); fFrameTime = 1.f; };

			button = AddObject(Button);
			button->SetButton(GetTex(L"MainButton"), Vector3(815.f, 609.f, 0.f), 223, 55);
			button->func = [&]() { SCENE->ChangeScene(L"LoseScene"); fFrameTime = 1.f; };
		}
	}
}
