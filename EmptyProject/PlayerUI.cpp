#include "DXUT.h"
#include "PlayerUI.h"


PlayerUI::PlayerUI()
{
}


PlayerUI::~PlayerUI()
{
}

void PlayerUI::Init()
{
	lpNormalTex = GetTex(L"NormalBulletDisplay");
	lpNwayTex = GetTex(L"NWayBulletDisplay");
	lpHommingTex = GetTex(L"HommingMissile");
	lpNuClearTex = GetTex(L"NuClearDisplay");
	
	lpWeapon = AC(UIRenderer);
	lpWeapon->lpTex = lpNormalTex;
	lpWeapon->vPos = Vector3(26.f, 553.f, 0.f);
	
	lpWeaponText = AC(Text);
	lpWeaponText->str = L"30";
	lpWeaponText->vPos = Vector3(210.f, 619.f, 0.f);

	lpStateBar = AC(UIRenderer);
	lpStateBar->lpTex = GetTex(L"StateBar");
	lpStateBar->vPos = Vector3(26.f, 18.f, 0.f);

	lpStateBarLifeText = AC(Text);
	lpStateBarLifeText->str = L"3";
	lpStateBarLifeText->vPos = Vector3(314.f, 87.f, 0.f);

	lpStateBarNuClearText = AC(Text);
	lpStateBarNuClearText->str = L"2";
	lpStateBarNuClearText->vPos = Vector3(371.f, 120.f, 0.f);

	lpScoreBar = AC(UIRenderer);
	lpScoreBar->lpTex = GetTex(L"ScoreBar");
	lpScoreBar->vPos = Vector3(939.f, 28.f, 0.f);

	lpScoreBarText = AC(Text);
	lpScoreBarText->str = L"100000";
	lpScoreBarText->vPos = Vector3(995.f, 108.f, 0.f);
	
	lpDoubleJump = AC(UIRenderer);
	lpDoubleJump->lpTex = GetTex(L"D");
	lpDoubleJump->vPos = Vector3(1150.f, 237.f, 0.f);
	lpDoubleJump->bEnable = false;

	lpNwayBullet = AC(UIRenderer);
	lpNwayBullet->lpTex = GetTex(L"M");
	lpNwayBullet->vPos = Vector3(1150.f, 360.f, 0.f);
	lpNwayBullet->bEnable = false;

	lpRangeUp = AC(UIRenderer);
	lpRangeUp->lpTex = GetTex(L"R");
	lpRangeUp->vPos = Vector3(1150.f, 487.f, 0.f);
	lpRangeUp->bEnable = false;

	lpSpeedUp = AC(UIRenderer);
	lpSpeedUp->lpTex = GetTex(L"S");
	lpSpeedUp->vPos = Vector3(1150.f, 604.f, 0.f);
	lpSpeedUp->bEnable = false;
}

void PlayerUI::AddScore(int iCount)
{
	MAP->iScore += iCount;
	
	wchar_t str[7];
	swprintf(str, L"%06d", iCount);
	lpScoreBarText->str = str;
}

void PlayerUI::SetNuClear(int iCount)
{
	wchar_t str[2];
	swprintf(str, L"%d", iCount);
	lpStateBarNuClearText->str = str;
}

void PlayerUI::SetLife(int iCount)
{
	wchar_t str[2];
	swprintf(str, L"%d", iCount);
	lpStateBarLifeText->str = str;
}

void PlayerUI::SetWeapon(PLAYERWEAPON eType, int iCount)
{
	switch (eType)
	{
	case e_base:
		lpWeapon->lpTex = lpNormalTex;
		lpWeaponText->bEnable = false;
		break;
	case e_homming:
		lpWeapon->lpTex = lpHommingTex;
		lpWeaponText->bEnable = true;
		break;
	case e_nuclear:
		lpWeapon->lpTex = lpNuClearTex;
		lpWeaponText->bEnable = true;
		break;
	}

	wchar_t str[4];
	swprintf(str, L"%03d", iCount);
	lpWeaponText->str = str;
}

void PlayerUI::SetDoubleJump(bool b)
{
	lpDoubleJump->bEnable = b;
}

void PlayerUI::SetNwayBullet(bool b)
{
	lpNwayBullet->bEnable = b;
}

void PlayerUI::SetRangeUp(bool b)
{
	lpRangeUp->bEnable = b;
}

void PlayerUI::SetSpeedUp(bool b)
{
	lpSpeedUp->bEnable = b;
}
