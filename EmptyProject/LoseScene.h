#pragma once
#include "Scene.h"
class LoseScene :
	public Scene
{
public:
	LoseScene();
	virtual ~LoseScene();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;

};

