#pragma once
#include "GameObject.h"
class HommingMissile :
	public GameObject
{
public:
	GameObject * lpTaget = nullptr;
	
public:
	HommingMissile();
	virtual ~HommingMissile();
	
	virtual void Init()	override;
	virtual void Update()	override;

};

