#include "DXUT.h"
#include "Item.h"


Item::Item()
{
}


Item::~Item()
{
}

void Item::SetItem(RefV3 vPos, ITEMTYPE _eType)
{
	eType = _eType;

	switch (eType)
	{
	case ITEM_D:
		break;
	case ITEM_H:
		break;
	case ITEM_M:
		break;
	case ITEM_N:
		break;
	case ITEM_R:
		break;
	case ITEM_S:
		break;
	case ITEM_U:
		break;
	default:
		break;
	}
}
