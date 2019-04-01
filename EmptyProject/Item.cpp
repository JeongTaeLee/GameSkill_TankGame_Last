#include "DXUT.h"
#include "Item.h"
#include "PlayerTank.h"

Item::Item()
{
}


Item::~Item()
{
}

void Item::Init()
{
	transform->vScale = Vector3(0.2f, 0.2f, 0.2f);

	AC(PixelCollider);
	lpPixelCollider->iHeight = 5.f;
	
	AC(RigidBody);
	lpRigidBody->fMass = 0.5f;
	lpRigidBody->bUseGravity = true;


	AC(Collider);
	lpCollider->SetCollider(10.f, Vector3(0.f, 0.f, 0.f));
}

void Item::SetItem(RefV3 vPos, ITEMTYPE _eType)
{
	transform->vPos = vPos;
	transform->vRot.y = D3DXToRadian(180.f);

	AC(ShaderRenderer);
	lpShaderRenderer->lpEffect = GetEffect(L"Lighting");

	eType = _eType;

	switch (eType)
	{
	case ITEM_D:	
		lpShaderRenderer->lpMesh= GetMesh_(L"D");
		func = [&](PlayerTank * tank) {
			tank->SetDoubleJump();
		};
		break;
	case ITEM_H:
		lpShaderRenderer->lpMesh = GetMesh_(L"H");
		func = [&](PlayerTank * tank) {
			tank->AddHomming();
		};
		break;
	case ITEM_M:
		lpShaderRenderer->lpMesh = GetMesh_(L"M");
		func = [&](PlayerTank * tank) {
			tank->SetNwayBullet();
		};
		break;
	case ITEM_N:
		lpShaderRenderer->lpMesh = GetMesh_(L"N");
		func = [&](PlayerTank * tank) {
			tank->AddNuClear();
		};
		break;
	case ITEM_R:
		lpShaderRenderer->lpMesh = GetMesh_(L"R");
		func = [&](PlayerTank * tank) {
			tank->SetNwayBullet();
		};
		break;
	case ITEM_S:
		lpShaderRenderer->lpMesh = GetMesh_(L"S");
		func = [&](PlayerTank * tank) {
			tank->SetSpeedUp();
		};
		break;
	case ITEM_U:
		lpShaderRenderer->lpMesh = GetMesh_(L"U");
		func = [&](PlayerTank * tank) {
			tank->SetUpgrad();
		};
		break;
	default:
		break;
	}
}

void Item::ReceiveCollider(Collider * lpOther)
{
	if (lpOther->gameObject->sTag == "Player")
	{
		func((PlayerTank*)lpOther->gameObject);
		bDestroy = true;
		bActive = false;
	}
}
