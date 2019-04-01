#include "DXUT.h"
#include "MainGame.h"

#include "LoadingScene.h"
#include "Stage01.h"
#include "Stage02.h"

#include "LoseScene.h"	
#include "VictoryScene.h"
#include "MainMenu.h"
MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

void MainGame::Init()
{
	g_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	g_device->SetRenderState(D3DRS_LIGHTING, false);

	SCENE->Add(L"Loading", new LoadingScene);
	SCENE->Add(L"MainMenu", new MainMenu);
	SCENE->Add(L"Stage01", new Stage01);
	SCENE->Add(L"Stage02", new Stage02);

	SCENE->Add(L"VictoryScene", new VictoryScene);
	SCENE->Add(L"LoseScene", new LoseScene);

	SCENE->ChangeScene(L"Loading");
}

void MainGame::Release()
{
	MapManager::ReleaseInst();
	SceneManager::ReleaseInst();
	ObjectManager::ReleaseInst();
	ResourceManager::ReleaseInst();
	InputManager::ReleaseInst();
	CameraManger::ReleaseInst();
	SoundManager::ReleaseInst();
}

void MainGame::Update()
{
	INPUT->Update();

	if (KEYDOWN(VK_F4))
		SCENE->ChangeScene(L"MainMenu");
	else if (KEYDOWN(VK_F5))
		SCENE->ChangeScene(L"Stage01");
	else if (KEYDOWN(VK_F6))
		SCENE->ChangeScene(L"Stage02");
	SCENE->Update();
	OBJECT->Update();
	CAMERA->Update();
}

void MainGame::Render()
{
	CAMERA->SetViewMatrix();
	OBJECT->Render();
}
