#include "DXUT.h"
#include "PlayerGun.h"
#include "PlayerBullet.h"
#include "PlayerTank.h"

PlayerGun::PlayerGun()
{
}


PlayerGun::~PlayerGun()
{
}

void PlayerGun::Init()
{
	AC(ShaderRenderer);
	lpShaderRenderer->lpEffect = GetEffect(L"Lighting");

	lpA = GetMesh_(L"PlayerA_H");
	lpB = GetMesh_(L"PlayerB_H");
	lpC = GetMesh_(L"PlayerC_H");
	SetGun(e_gun01);
}

void PlayerGun::Update()
{
	Vector2 vMousePos = INPUT->GetMPos();

	Vector3 v2Dpos;
	WorldTo2D(v2Dpos, transform->vWorldPos);
	
	Vector3 vDir = vMousePos - Vector2(v2Dpos.x, v2Dpos.y);
	D3DXVec3Normalize(&vDir, &vDir);

	float fAngle = atan2f(vDir.y, vDir.x);
	transform->vRot.x = fAngle;
}

void PlayerGun::Attack(RefV3 vRight, bool _bNwayBullet)
{
	Matrix matRot = transform->matRot * transform->lpParent->transform->matRot;
	
	Quaternion qRot;
	D3DXQuaternionRotationMatrix(&qRot, &matRot);

	float fDeleteTime = 0.5f;

	switch (eGunType)
	{
	case e_noneGunType:
		break;
	case e_gun01:
		fDeleteTime = 0.5f;
		break;
	case e_gun02:
		fDeleteTime = 0.7f;
		break;
	case e_gun03:
		fDeleteTime = 1.0f;
		break;
	}

	AddObject(PlayerBullet)->SetBullet(E_PLAYERBULLET_02, transform->vWorldPos, qRot, 300.f, fDeleteTime);

	if (_bNwayBullet)
	{
		Matrix matRotLeft;
		Matrix matRotRight;

		D3DXMatrixRotationAxis(&matRotLeft, &vRight, D3DXToRadian(10.f));
		D3DXMatrixRotationAxis(&matRotRight, &vRight, -D3DXToRadian(10.f));

		matRotLeft = matRot * matRotLeft;
		matRotRight = matRot * matRotRight;

		Quaternion qRotLeft;
		D3DXQuaternionRotationMatrix(&qRotLeft, &matRotLeft);

		Quaternion qRotRight;
		D3DXQuaternionRotationMatrix(&qRotRight, &matRotRight);

		AddObject(PlayerBullet)->SetBullet(E_PLAYERBULLET_02, transform->vWorldPos, qRotLeft, 400.f, 0.5f);
		AddObject(PlayerBullet)->SetBullet(E_PLAYERBULLET_02, transform->vWorldPos, qRotRight, 400.f, 0.5f);
	}
}

void PlayerGun::SetGun(PLAYERGUNTYPE _eGunType)
{
	if (eGunType != _eGunType)
	{
		eGunType = _eGunType;

		switch (eGunType)
		{
		case e_gun01:
			lpShaderRenderer->lpMesh = lpA;
			transform->vPos = Vector3(0.f, 50.f, -20.f);
			break;
		case e_gun02:
			lpShaderRenderer->lpMesh = lpB;
			transform->vPos = Vector3(0.f, 50.f, -20.f);
			break;
		case e_gun03:
			lpShaderRenderer->lpMesh = lpC;
			transform->vPos = Vector3(0.f, 50.f, -20.f);
			break;
		default:
			break;
		}
	}
}
