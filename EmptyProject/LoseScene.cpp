#include "DXUT.h"
#include "LoseScene.h"
#include "AnimationView.h"
#include "Ranking.h"

LoseScene::LoseScene()
{
}


LoseScene::~LoseScene()
{
}

void LoseScene::Init()
{

	LoadTexs(L"LoseEnding%d", L"./rs/Ending/(%d).jpg", 1, 41);

	AnimationView * lpAni = AddObject(AnimationView);
	lpAni->SetAnimation(L"LoseEnding%d", 1, 41);
	lpAni->func = [&]() {
		AddObject(Ranking);
		return false;
	};
	
	SOUND->Play(L"Failed", true);
}

void LoseScene::Release()
{
	SOUND->Stop(L"Failed");

	OBJECT->Reset();
}

void LoseScene::Update()
{
}
