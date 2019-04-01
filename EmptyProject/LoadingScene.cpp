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
	LoadMeshs(L"PlayerADie%d", L"./rs/PlayerA_die/PlayerA_Die%d.obj", 0, 5);

	//PlayerB
	LoadMeshs(L"PlayerB%d", L"./rs/PlayerB/PlayerB%d.obj", 0, 1);
	AdMesh(L"PlayerB_H", L"./rs/PlayerB/PlayerB_/PlayerB_.obj");
	LoadMeshs(L"PlayerBDie%d", L"./rs/PlayerB_die/PlayerB_Die%d.obj", 0, 5);

	//PlayerC
	LoadMeshs(L"PlayerC%d", L"./rs/PlayerC/PlayerC%d.obj", 0, 1);
	AdMesh(L"PlayerC_H", L"./rs/PlayerC/PlayerC_/PlayerC_.obj");
	LoadMeshs(L"PlayerCDie%d", L"./rs/PlayerC_die/PlayerC_Die%d.obj", 0, 5);

	//MonsterA
	AdMesh(L"MonsterA1", L"./rs/MonsterA1/MonsterA1.obj");
	LoadMeshs(L"MonsterA1Die%d", L"./rs/MonsterA1_die/MonsterA_die%d.obj", 0, 20);
	AdMesh(L"MonsterA2", L"./rs/MonsterA2/MonsterA2.obj");
	LoadMeshs(L"MonsterA2Die%d", L"./rs/MonsterA2_Die/MonsterA2_die%d.obj", 0, 20);

	//MonsterB
	AdMesh(L"MonsterB1", L"./rs/MonsterB/MonsterB.obj");
	LoadMeshs(L"MonsterB1Die%d", L"./rs/MonsterB1_Die/MonsterB_Die%d.obj", 0, 20);
	AdMesh(L"MonsterB2", L"./rs/MonsterB2/MonsterB2.obj");
	LoadMeshs(L"MonsterB2Die%d", L"./rs/MonsterB2_Die/MonsterB_Die%d.obj", 0, 20);

	//Bullet
	AdMesh(L"NormalBullet", L"./rs/BulletA_Nomal/BulletA.obj");
	AdMesh(L"AirBullet", L"./rs/BulletC_Air/BulletC.obj");
	AdMesh(L"HommingMissile", L"./rs/BulletB_Homming/BulletB.obj");
	AdMesh(L"NuClear", L"./rs/BulletD_Nuclear/BulletD.obj");

	//Stone
	LoadMeshs(L"Stone%d", L"./rs/Stone/Stone%d.obj", 0, 20);

	//LockOnCrossHair
	AdTex(L"LockOnCrossHair", L"./rs/UI/Target.png");

	//Item
	AdMesh(L"D", L"./rs/D/D.obj");
	AdMesh(L"H", L"./rs/H/H.obj");
	AdMesh(L"M", L"./rs/M/M.obj");
	AdMesh(L"N", L"./rs/N/N.obj");
	AdMesh(L"R", L"./rs/R/R.obj");
	AdMesh(L"S", L"./rs/S/S.obj");
	AdMesh(L"U", L"./rs/U/U.obj");

	//WeaponDisplay
	AdTex(L"NormalBulletDisplay", L"./rs/UI/W/Normal.png");
	AdTex(L"NWayBulletDisplay", L"./rs/UI/W/3_way.png");
	AdTex(L"NuClearDisplay", L"./rs/UI/W/Nuclear.png");
	AdTex(L"HommingMissile", L"./rs/UI/W/Homming.png");

	AdTex(L"StateBar", L"./rs/UI/Life_Nuclear.png");
	AdTex(L"ScoreBar", L"./rs/UI/Score.png");

	AdTex(L"D", L"./rs/UI/Item/D.png");
	AdTex(L"M", L"./rs/UI/Item/M.png");
	AdTex(L"R", L"./rs/UI/Item/R.png");
	AdTex(L"S", L"./rs/UI/Item/S.png");

	AdTex(L"Display_M", L"./rs/UI/Item/3WayFlak.png");
	AdTex(L"Display_D", L"./rs/UI/Item/DoubleJump.png");
	AdTex(L"Display_R", L"./rs/UI/Item/HomingMissile.png");
	AdTex(L"Display_N", L"./rs/UI/Item/Nuclear.png");
	AdTex(L"Display_S", L"./rs/UI/Item/SpeedUp.png");
	AdTex(L"Display_U", L"./rs/UI/Item/TankUpgrade.png");


	AdMesh(L"Stage01", L"./rs/Stage1/Stage1.obj");
	AdMesh(L"Stage01SkyBox", L"./rs/SkyBox/SkyBox.obj");
	AdTex(L"Stage01Height", L"./rs/Stage1/Stage1_.png");
	AdTex(L"Stage01Width", L"./rs/Stage1/Stage1B_.png");
	
	//Explosion
	LoadTexs(L"BulletExplosion%d", L"./rs/Explosion_EffectC/(%d).png", 1, 41);
	LoadTexs(L"DieExplosionA%d", L"./rs/Explosion_EffectB/(%d).png", 1, 41);
	LoadTexs(L"DieExplosionB%d", L"./rs/Explosion_EffectB_/(%d).png", 1, 41);

	bEnd = true;
}
