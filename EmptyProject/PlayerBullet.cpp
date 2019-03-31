#include "DXUT.h"
#include "PlayerBullet.h"


PlayerBullet::PlayerBullet()
{
	sTag = "PlayerBullet";
}


PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Init()
{
	transform->eType = TransformUpdateType::TU_2;

	AC(PixelCollider);
	lpPixelCollider->funcCall = [&](){
		bDestroy = true;
	};
}

void PlayerBullet::Update()
{
	GetLookAtS(transform->qRot, lpRigidBody->vDir, 0.2f);

	if (fElapsed >= fDelay)
	{
		bDestroy = true;
	}
	else
		fElapsed += Et;
}

void PlayerBullet::SetBullet(PLAYERBULLETYPE type, RefV3 vPos, Quaternion qRot, float _fPower, float fTime)
{
	transform->vPos = vPos;
	fPower = _fPower;
	fDelay = fTime;

	Matrix matRot;
	D3DXMatrixRotationQuaternion(&matRot, &qRot);
	D3DXVec3TransformCoord(&vDir, &vDir, &matRot);

	AC(ShaderRenderer);
	lpShaderRenderer->lpEffect = GetEffect(L"Lighting");

	switch (type)
	{
	case E_PLAYERBULLET_01:
		lpShaderRenderer->lpMesh = GetMesh_(L"PlayerBullet01");
		transform->vScale = Vector3(0.2f, 0.2f, 0.2f);
		break;
	case E_PLAYERBULLET_02:
		lpShaderRenderer->lpMesh = GetMesh_(L"PlayerBullet02");
		transform->vScale = Vector3(0.2f, 0.2f, 0.2f);
		break;
	default:
		break;
	}

	AC(Collider);
	lpCollider->SetCollider(10.f, Vector3(0.f, 0.f, 0.f));

	AC(RigidBody);
	lpRigidBody->fMass = 1.f;
	lpRigidBody->bUseGravity = true;
	lpRigidBody->AddForce(vDir * fPower);

	GetLookAtS(transform->qRot, vDir, 0.2f);
}

void PlayerBullet::ReceiveCollider(Collider * lpOther)
{
	if (lpOther->gameObject->sTag == "Monster")
	{
		bDestroy = true;
	}
}
