#include "DXUT.h"
#include "LoadingScene.h"


LoadingScene::LoadingScene()
{
}


LoadingScene::~LoadingScene()
{
}

void LoadingScene::Init()
{
	thread01 = thread([&]() {Loading(); });

}

void LoadingScene::Release()
{
	OBJECT->Reset();
}

void LoadingScene::Update()
{
	Sleep(1);

	if (bEnd)
	{
		if (thread01.joinable())
		{
			thread01.join();
			SCENE->ChangeScene(L"Stage01");
		}
	}
}

void LoadingScene::Loading()
{
	LoadMeshs(L"TankA%d", L"./rs/TankA/A%d.obj", 0, 1);
	AdMesh(L"TankA_H", L"./rs/TankA/TankA_/TankA_.obj");

	/*
	AdMesh(L"TestMap", L"./rs/TestMap/TestMap.obj");
	AdTex(L"TestMapWidth", L"./rs/TestMap/TestMapWidth.png");
	AdTex(L"TestMapHeight", L"./rs/TestMap/TestMapHeight.png");
	*/
	AdMesh(L"Stage01", L"./rs/Stage1/Stage1.obj");
	AdTex(L"Stage01Height", L"./rs/Stage1/Stage1_.png");
	AdTex(L"Stage01Width", L"./rs/Stage1/Stage1B_.png");
	bEnd = true;
}
