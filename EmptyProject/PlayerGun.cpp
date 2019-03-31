#include "DXUT.h"
#include "PlayerGun.h"
#include "PlayerBullet.h"

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

void PlayerGun::Attack()
{
	Matrix matRot = transform->matRot * transform->lpParent->transform->matRot;
	
	Quaternion qRot;
	D3DXQuaternionRotationMatrix(&qRot, &matRot);

	AddObject(PlayerBullet)->SetBullet(E_PLAYERBULLET_02, transform->vWorldPos, qRot, 400.f, 0.5f);
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
			break;
		case e_gun03:
			break;
		default:
			break;
		}
	}
}
