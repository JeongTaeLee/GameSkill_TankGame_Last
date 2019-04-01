#pragma once
#include "GameObject.h"
#include "Item.h"
class ItemUI :
	public GameObject
{
public:
	ItemUI();
	virtual ~ItemUI();

	void SetItemUI(ITEMTYPE eItemType);

};

