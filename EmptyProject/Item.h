#pragma once
#include "GameObject.h"

enum ITEMTYPE
{
	ITEM_D,
	ITEM_H,
	ITEM_M,
	ITEM_N,
	ITEM_R,
	ITEM_S,
	ITEM_U,
};

class Item :
	public GameObject
{
public:
	ITEMTYPE eType;
public:
	Item();
	virtual ~Item();

	virtual void Init()	override;
	
	void SetItem(RefV3 vPos, ITEMTYPE _eType);

};

