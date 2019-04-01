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
class PlayerTank;
class Item :
	public GameObject
{
public:
	PlayerTank * lpTank = nullptr;

	ITEMTYPE eType = ITEM_D;

	function < void(PlayerTank * tank) > func = nullptr;
public:
	Item();
	virtual ~Item();

	virtual void Init()	override;
	virtual void Update()	override;

	void SetItem(RefV3 vPos, ITEMTYPE _eType);

	virtual void ReceiveCollider(Collider * lpOther) override;

};

