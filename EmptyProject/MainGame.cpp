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
	ShowCursor(false);

	D3DXCreateTextureFromFileEx(g_device, L"./rs/UI/MouseCursor.png", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, nullptr, nullptr, &mouse);

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
	SAFE_RELEASE(mouse);
	ShowCursor(true);

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

	RESOURCE->lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	Matrix matPos;
	D3DXMatrixTranslation(&matPos, INPUT->GetMPos().x, INPUT->GetMPos().y, 0.f);
	RESOURCE->lpSprite->SetTransform(&matPos);
	RESOURCE->lpSprite->Draw(mouse, nullptr, &Vector3(83.f / 2.f, 83.f / 2.f, 0.f), nullptr, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
	RESOURCE->lpSprite->End();
}
