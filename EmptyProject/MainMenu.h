#pragma once
#include "Scene.h"
class MainMenu :
	public Scene
{
public:
	GameObject * particle = nullptr;
public:
	MainMenu();
	virtual ~MainMenu();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
};

