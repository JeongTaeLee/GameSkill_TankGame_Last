#include "DXUT.h"
#include "LoadingScene.h"
#include "AnimationView.h"

LoadingScene::LoadingScene()
{
}


LoadingScene::~LoadingScene()
{
}

void LoadingScene::Init()
{
	SOUND->AddSound(L"IntroLoading", L"./rs/Music/IntroLoding.wav");

	thread01 = thread([&]() {Loading(); });

	LoadTexs(L"Intro%d", L"./rs/Intro/(%d).jpg", 1, 141);
	LoadTexs(L"Loading%d", L"./rs/Loading/(%d).jpg", 1, 31);

	AnimationView * lpAni = AddObject(AnimationView);
	lpAni->SetAnimation(L"Intro%d", 1, 141);
	SOUND->Play(L"IntroLoading", true, 0);

	lpAni->func = []() {  

		Sleep(1000);
		
		AnimationView * ani = AddObject(AnimationView);
		ani->SetAnimation(L"Loading%d", 1, 31);
		ani->func = []() {
			return true;
		};

		return false; 
	};
}

void LoadingScene::Release()
{
	SOUND->Stop(L"IntroLoading");
	OBJECT->Reset();
}

void LoadingScene::Update()
{
	Sleep(10);

	if (bEnd)
	{
		if (thread01.joinable())
		{
			thread01.join();
			SCENE->ChangeScene(L"MainMenu");
		}
	}
}

void LoadingScene::Loading()
{
	SOUND->AddSound(L"Click", L"./rs/Music/bounce.wav");
	SOUND->AddSound(L"Explosion", L"./rs/Music/Explosion.wav");
	SOUND->AddSound(L"Fire", L"./rs/Music/Fire.wav");
	SOUND->AddSound(L"Ingame", L"./rs/Music/Ingame.wav");
	SOUND->AddSound(L"Start", L"./rs/Music/Start.wav");


	AdEffect(L"Lighting", L"./Lighting.fx");

	//PlayerA
	LoadMeshs(L"PlayerA%d", L"./rs/PlayerA/PlayerA%d.obj", L"PlayerA", 0, 1);
	AdMesh(L"PlayerA_H", L"./rs/PlayerA/PlayerA_/TankA_.obj");
	LoadMeshs(L"PlayerADie%d", L"./rs/PlayerA_die/PlayerA_Die%d.obj", L"PlayerADie", 0, 5);

	//PlayerB
	LoadMeshs(L"PlayerB%d", L"./rs/PlayerB/PlayerB%d.obj", L"PlayerB", 0, 1);
	AdMesh(L"PlayerB_H", L"./rs/PlayerB/PlayerB__/PlayerB__.obj");
	LoadMeshs(L"PlayerBDie%d", L"./rs/PlayerB_die/PlayerB_Die%d.obj", L"PlayerBDie", 0, 5);

	//PlayerC
	LoadMeshs(L"PlayerC%d", L"./rs/PlayerC/PlayerC%d.obj", L"PlayerC", 0, 1);
	AdMesh(L"PlayerC_H", L"./rs/PlayerC/PlayerC__/PlayerC__.obj");
	LoadMeshs(L"PlayerCDie%d", L"./rs/PlayerC_die/PlayerC_Die%d.obj", L"PlayerCDie", 0, 5);

	//MonsterA
	AdMesh(L"MonsterA1", L"./rs/MonsterA1/MonsterA1.obj");
	LoadMeshs(L"MonsterA1Die%d", L"./rs/MonsterA1_die/MonsterA_die%d.obj", L"MonsterA1Die", 0, 20);
	AdMesh(L"MonsterA2", L"./rs/MonsterA2/MonsterA2.obj");
	LoadMeshs(L"MonsterA2Die%d", L"./rs/MonsterA2_Die/MonsterA2_die%d.obj", L"MonsterA2Die", 0, 20);

	//MonsterB
	AdMesh(L"MonsterB1", L"./rs/MonsterB/MonsterB.obj");
	LoadMeshs(L"MonsterB1Die%d", L"./rs/MonsterB1_Die/MonsterB_Die%d.obj", L"MonsterB1Die", 0, 20);
	AdMesh(L"MonsterB2", L"./rs/MonsterB2/MonsterB2.obj");
	LoadMeshs(L"MonsterB2Die%d", L"./rs/MonsterB2_Die/MonsterB_Die%d.obj", L"MonsterB2Die", 0, 20);

	//Bullet
	AdMesh(L"NormalBullet", L"./rs/BulletA_Nomal/BulletA.obj");
	AdMesh(L"AirBullet", L"./rs/BulletC_Air/BulletC.obj");
	AdMesh(L"HommingMissile", L"./rs/BulletB_Homing/BulletB.obj");
	AdMesh(L"NuClear", L"./rs/BulletD_Nuclear/BulletD.obj");
	AdMesh(L"MonsterBullet", L"./rs/MonsterBulletA/MB_A.obj");

	//Stone
	LoadMeshs(L"Stone%d", L"./rs/Stone/Stone%d.obj", L"Stone", 0, 20);

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

	AdTex(L"Display_R", L"./rs/UI/Item/IncreaseRange.png");
	AdTex(L"Display_M", L"./rs/UI/Item/3WayFlak.png");
	AdTex(L"Display_D", L"./rs/UI/Item/DoubleJump.png");
	AdTex(L"Display_H", L"./rs/UI/Item/HomingMissile.png");
	AdTex(L"Display_N", L"./rs/UI/Item/Nuclear.png");
	AdTex(L"Display_S", L"./rs/UI/Item/SpeedUp.png");
	AdTex(L"Display_U", L"./rs/UI/Item/TankUpgrade.png");

	AdTex(L"CheckPoint", L"./rs/UI/CheckPoint.png");

	//Clear
	AdTex(L"GameClear", L"./rs/UI/GameClear.png");
	AdTex(L"GameOver", L"./rs/UI/GameOver.png");
	AdTex(L"NextStageButton", L"./rs/UI/Nextstage.png");
	AdTex(L"MainButton", L"./rs/UI/MAIN.png");
	AdTex(L"RetryButton", L"./rs/UI/Retry.png");
	AdTex(L"RankingInput", L"./rs/UI/Ranking.png");


	AdMesh(L"Stage01", L"./rs/Stage1/Stage1.obj");
	AdMesh(L"Stage01SkyBox", L"./rs/SkyBox/SkyBox.obj");
	AdTex(L"Stage01Height", L"./rs/Stage1/Stage1_.png");
	AdTex(L"Stage01Width", L"./rs/Stage1/Stage1B_.png");

	AdMesh(L"Stage02", L"./rs/Stage2/Stage2.obj");
	AdMesh(L"Stage02SkyBox", L"./rs/Stage2/SkyBox/Skybox.obj");
	AdTex(L"Stage02Height", L"./rs/Stage2/A_.png");
	AdTex(L"Stage02Width", L"./rs/Stage2/B_.png");

	//Main
	AdTex(L"MainBackGroundA", L"./rs/Main/MainA.png");
	AdTex(L"MainBackGroundB", L"./rs/Main/MainB.png");
	AdTex(L"MainBackGroundC", L"./rs/Main/MainC.png");

	AdTex(L"StartButton", L"./rs/Main/A/Start.png");
	
	AdTex(L"HowtoButton", L"./rs/Main/A/Howto.png");
	AdTex(L"HowtoScreen", L"./rs/Main/A/Howto_.png");

	AdTex(L"InfoButton", L"./rs/Main/A/Info.png");
	AdTex(L"InfoScreen", L"./rs/Main/A/Info_.png");

	AdTex(L"RankButton", L"./rs/Main/A/Rank.png");
	AdTex(L"RankScreen", L"./rs/Main/A/Rank_.png");

	AdTex(L"CreditButton", L"./rs/Main/A/Credit.png");
	AdTex(L"CreditScreen", L"./rs/Main/A/Credit_.png");
	
	//Explosion
	LoadTexs(L"BulletExplosion%d", L"./rs/Explosion_EffectC/(%d).png", 1, 41);
	LoadTexs(L"DieExplosionA%d", L"./rs/Explosion_EffectB/(%d).png", 1, 41);
	LoadTexs(L"DieExplosionB%d", L"./rs/Explosion_EffectB_/(%d).png", 1, 41);

	bEnd = true;
}
