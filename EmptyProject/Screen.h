#pragma once
#include "GameObject.h"
class Screen :
	public GameObject
{
public:
	Screen();
	virtual ~Screen();

	virtual void Update()	override;

	void SetScreen(texture * lpScreen);
};

