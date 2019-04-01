#pragma once
#include "Scene.h"



class LoadingScene :
	public Scene
{
public:
	thread thread01;

	bool bEnd = false;

public:
	LoadingScene();
	virtual ~LoadingScene();

	virtual void Init()	override;
	virtual void Release()	override;
	virtual void Update()	override;

	void Loading();

};

