#pragma once
#include "GameObject.h"
class Button :
	public GameObject
{
public:
	RECT reRect = { 0 };

	function <void()> func;
public:
	Button();
	virtual ~Button();

	virtual void Update()	override;

	void SetButton(texture * lpButtonTexture, RefV3 vPos, int Width, int Height);
};

