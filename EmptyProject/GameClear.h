#pragma once
#include "GameObject.h"
class GameClear :
	public GameObject
{
public:
	bool bCompleteProcess = false;
public:
	GameClear();
	virtual ~GameClear();

	virtual void Init()	override;
	virtual void Update()	override;
};

