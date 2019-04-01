#pragma once
#include "GameObject.h"
#include "PlayerTank.h"

class PlayerUI :
	public GameObject
{
public:
	texture * lpNormalTex = nullptr;
	texture * lpNwayTex = nullptr;
	texture * lpHommingTex = nullptr;
	texture * lpNuClearTex = nullptr;
	
	UIRenderer * lpWeapon = nullptr;
	Text * lpWeaponText = nullptr;
	
	UIRenderer * lpStateBar = nullptr;
	Text * lpStateBarLifeText = nullptr;
	Text * lpStateBarNuClearText = nullptr;

	UIRenderer * lpScoreBar = nullptr;
	Text * lpScoreBarText = nullptr;

	UIRenderer * lpDoubleJump = nullptr;
	UIRenderer * lpNwayBullet = nullptr;
	UIRenderer * lpRangeUp = nullptr;
	UIRenderer * lpSpeedUp = nullptr;
public:
	PlayerUI();
	virtual ~PlayerUI();

	virtual void Init()	override;

	void AddScore(int iCount);
	void SetNuClear(int iCount);
	void SetLife(int iCount);
	void SetWeapon(PLAYERWEAPON eType, int iCount);

	void SetDoubleJump(bool b);
	void SetNwayBullet(bool b);
	void SetRangeUp(bool b);
	void SetSpeedUp(bool b);

};

