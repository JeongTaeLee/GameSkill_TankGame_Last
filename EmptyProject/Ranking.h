#pragma once
#include "GameObject.h"
class Ranking :
	public GameObject
{
public:
	int iCount = 0;

	Text * lpBastScore = nullptr;
	Text * lpName = nullptr;
	Text * lpScore = nullptr;
public:
	Ranking();
	virtual ~Ranking();

	virtual void Init()	override;
	virtual void Update() override;

	
};

