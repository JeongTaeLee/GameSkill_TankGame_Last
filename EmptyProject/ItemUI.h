#pragma once
#include "GameObject.h"
#include "Item.h"
class ItemUI :
	public GameObject
{
private:
	float fDelay = 1.f;
	float fElapsed = 0.f;
public:
	ItemUI();
	virtual ~ItemUI();

	virtual void Update() override;

	void SetItemUI(ITEMTYPE eItemType);
};

