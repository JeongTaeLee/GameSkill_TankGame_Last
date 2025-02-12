#include "DXUT.h"
#include "VictoryScene.h"

#include "AnimationView.h"
#include "Ranking.h"

VictoryScene::VictoryScene()
{
}


VictoryScene::~VictoryScene()
{
}

void VictoryScene::Init()
{

	LoadTexs(L"VictroyEnding%d", L"./rs/Ending_/(%d).jpg", 1, 41);

	AnimationView * lpAni = AddObject(AnimationView);
	lpAni->SetAnimation(L"VictroyEnding%d", 1, 41);
	lpAni->func = [&]() {
		AddObject(Ranking);
		return false;
	};

	SOUND->Play(L"Victory", true);
}

void VictoryScene::Release()
{
	SOUND->Stop(L"Victory");
	OBJECT->Reset();
}

void VictoryScene::Update()
{
}
