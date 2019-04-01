#include "DXUT.h"
#include "MainMenu.h"
#include "Button.h"
#include "Screen.h"
#include "RankScreen.h"
void CreateButton(texture * lpTex, RefV3 vPos, function<void()> func)
{
	Button * button = AddObject(Button);
	button->SetButton(lpTex, vPos, lpTex->info.Width, lpTex->info.Height);
	button->func = func;
}

MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
	MAP->LoadScore();

	SOUND->Play(L"IntroLoading", true);

	GameObject * object = AddObject(GameObject);
	object->AC(UIRenderer)->lpTex = GetTex(L"MainBackGroundA");

	particle = AddObject(GameObject);
	particle->AC(UIRenderer)->lpTex = GetTex(L"MainBackGroundB");

	object = AddObject(GameObject);
	object->AC(UIRenderer)->lpTex = GetTex(L"MainBackGroundC");

	CreateButton(GetTex(L"StartButton"), Vector3(156, 627, 0.f), [&](){
		SCENE->ChangeScene(L"Stage01");
	});
	CreateButton(GetTex(L"HowtoButton"), Vector3(403.f, 627.f, 0.f), [&]() {
		AddObject(Screen)->SetScreen(GetTex(L"HowtoScreen"));
	});
	CreateButton(GetTex(L"InfoButton"), Vector3(650.f, 627.f, 0.f), [&]() {
		AddObject(Screen)->SetScreen(GetTex(L"InfoScreen"));
	});
	CreateButton(GetTex(L"RankButton"), Vector3(897, 627.f, 0.f), [&]() {
		AddObject(RankScreen);
	});
	CreateButton(GetTex(L"CreditButton"), Vector3(1144.f, 627.f, 0.f), [&]() {
		AddObject(Screen)->SetScreen(GetTex(L"CreditScreen"));
	});

}

void MainMenu::Release()
{
	SOUND->Stop(L"IntroLoading");
	OBJECT->Reset();
}

void MainMenu::Update()
{
}
