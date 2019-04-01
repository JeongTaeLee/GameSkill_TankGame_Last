#pragma once
#include "GameObject.h"
class GameOver :
	public GameObject
{
public:
	bool bCompleteProcess = false;
public:
	GameOver();
	virtual ~GameOver();

	virtual void Init()	override;
	virtual void Update()	override;
};

