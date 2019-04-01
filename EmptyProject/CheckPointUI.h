#pragma once
#include "GameObject.h"
class CheckPointUI :
	public GameObject
{
public:
	float fElapsed = 0.f;
public:
	CheckPointUI();
	virtual ~CheckPointUI();

	virtual void Init()	override;
	virtual void Update()	override;
};

