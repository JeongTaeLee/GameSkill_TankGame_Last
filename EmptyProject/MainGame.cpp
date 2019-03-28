#include "DXUT.h"
#include "MainGame.h"


MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

void MainGame::Init()
{
}

void MainGame::Release()
{
	SceneManager::ReleaseInst();
	InputManager::ReleaseInst();
}

void MainGame::Update()
{
	INPUT->Update();
	SCENE->Update();
}

void MainGame::Render()
{
}
