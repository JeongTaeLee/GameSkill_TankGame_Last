#pragma once
#include "GameObject.h"
class SkyBox :
	public GameObject
{
public:
	SkyBox();
	virtual ~SkyBox();

	virtual void Init()	override;
	virtual void Update() override;

};

