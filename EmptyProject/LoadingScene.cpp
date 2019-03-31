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
	AdEffect(L"Lighting", L"./Lighting.fx");

	//PlayerA
	LoadMeshs(L"PlayerA%d", L"./rs/PlayerA/PlayerA%d.obj", 0, 1);
	AdMesh(L"PlayerA_H", L"./rs/PlayerA/PlayerA_/TankA_.obj");

	//PlayerB
	LoadMeshs(L"PlayerB%d", L"./rs/PlayerB/PlayerB%d.obj", 0, 1);
	AdMesh(L"PlayerB_H", L"./rs/PlayerB/PlayerB_/PlayerB_.obj");

	//PlayerC
	LoadMeshs(L"PlayerC%d", L"./rs/PlayerC/PlayerC%d.obj", 0, 1);
	AdMesh(L"PlayerC_H", L"./rs/PlayerC/PlayerC_/PlayerC_.obj");

	//MonsterA
	AdMesh(L"MonsterA1", L"./rs/MonsterA1/MonsterA1.obj");
	AdMesh(L"MonsterA2", L"./rs/MonsterA2/MonsterA2.obj");

	//Bullet
	AdMesh(L"PlayerBullet01", L"./rs/PlayerBullet01/BulletC.obj");
	AdMesh(L"PlayerBullet02", L"./rs/PlayerBullet02/BulletB.obj");

	//Stone
	LoadMeshs(L"Stone%d", L"./rs/Stone/Stone%d.obj", 0, 20);

	//LockOnCrossHair
	AdTex(L"LockOnCrossHair", L"./rs/UI/Target.png");

	AdMesh(L"Stage01", L"./rs/Stage1/Stage1.obj");
	AdMesh(L"Stage01SkyBox", L"./rs/SkyBox/SkyBox.obj");
	AdTex(L"Stage01Height", L"./rs/Stage1/Stage1_.png");
	AdTex(L"Stage01Width", L"./rs/Stage1/Stage1B_.png");
	
	bEnd = true;
}
