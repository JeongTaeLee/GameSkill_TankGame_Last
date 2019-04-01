#pragma once
#include "Scene.h"
class VictoryScene :
	public Scene
{
public:
	VictoryScene();
	virtual ~VictoryScene();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;

};

