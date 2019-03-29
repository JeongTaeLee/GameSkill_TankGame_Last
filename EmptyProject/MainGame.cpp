#include "DXUT.h"
#include "MainGame.h"

#include "LoadingScene.h"
#include "Stage01.h"

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
	SCENE->Add(L"Stage01", new Stage01);
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
}

void MainGame::Update()
{
	INPUT->Update();
	SCENE->Update();
	OBJECT->Update();
}

void MainGame::Render()
{
	CAMERA->SetViewMatrix();
	OBJECT->Render();
}
