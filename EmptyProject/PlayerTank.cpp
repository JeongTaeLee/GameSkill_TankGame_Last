#include "DXUT.h"
#include "PlayerTank.h"
#include "PlayerBullet.h"
#include "PlayerGun.h"

Vector3 PlayerTank::vSpawnPos = Vector3(0.f, 0.f, 0.f);

PlayerTank::PlayerTank()
{
	D3DXQuaternionIdentity(&qCameraRot);
}


PlayerTank::~PlayerTank()
{
}

void PlayerTank::Init()
{
	transform->eType = TransformUpdateType::TU_2;
	transform->vScale = Vector3(0.4f, 0.4f, 0.4f);

	lpGun = AddObject(PlayerGun);
	transform->AddChild(lpGun);

	lpCamera = CAMERA->GetCamera(L"PlayerCamera");
	CAMERA->ChanageCamera(L"PlayerCamera");
	lpCamera->vPos = Vector3(0.f, 100.f, -150.f);

	AC(Renderer);
	
	AC(Collider);
	lpCollider->SetCollider(25.f, Vector3(0.f, 0.f, 0.f));

	AC(Animater);
	lpAnimater->Add(L"MovingA", L"PlayerA%d", 0, 1, [&]() { if (!bMove) lpAnimater->Stop(0); });
	lpAnimater->Add(L"MovingB", L"PlayerB%d", 0, 1, [&]() { if (!bMove) lpAnimater->Stop(0); });
	lpAnimater->Add(L"MovingC", L"PlayerC%d", 0, 1, [&]() { if (!bMove) lpAnimater->Stop(0); });
	AC(RigidBody);
	lpRigidBody->bUseGravity = true;
	lpRigidBody->fMass = 2.3f;
	lpRigidBody->vDecrease.x = 0.94;
	lpRigidBody->vDecrease.z = 0.94;

	AC(PixelCollider);
	lpPixelCollider->vLeft = Vector3(-10.f, 0.f, 0.f);
	lpPixelCollider->vRight = Vector3(10.f, 0.f, 0.f);

	lpPixelCollider->funcCall = [&]()
	{
		bOnFloor = true;
		bDoubleJump = false;

		if (lpPixelCollider->eCallTypeLeft == PIXELTYPE::e_red 
			&& lpPixelCollider->eCallTypeRight == PIXELTYPE::e_red)
		{
			if (eState == E_PLAYERSTATE_IDLE)
				SetState(E_PLAYERSTATE_SPAWN);
		}
	};
	SetTank(e_tank01);
}

void PlayerTank::Release()
{
}

void PlayerTank::Update()
{
	switch (eState)
	{
	case E_PLAYERSTATE_DIE:
		break;
	case E_PLAYERSTATE_SPAWN:
		Spawn();
		break;
	case E_PLAYERSTATE_IDLE:
		Idle();
		Attack();
		ItemTimeCheck();
		break;
	}

	CameraSetting();
}

void PlayerTank::Idle()
{
	float fSpeed = 250.f;
	bMove = false;

	int iNowIndex = MAP->iWidthIndex;
	int iNextIndex = iNowIndex + 1;

	Vector3 vNowVector = MAP->vWidthMap[iNowIndex];
	Vector3 vNextVector = MAP->vWidthMap[iNextIndex];

	if (KEYPRESS('A'))
	{
		bBack = true;
		bMove = true;

		vLookDir = Vector3(vNowVector.x, transform->vPos.y, vNowVector.z) - transform->vPos;
		D3DXVec3Normalize(&vLookDir, &vLookDir);

		transform->vPos += vLookDir * (fSpeed * Et);
		
		if (transform->vPos.x < (vNowVector.x + 5.f))
		{
			if (iNowIndex != 0)
				--MAP->iWidthIndex;
		}
	}
	if (KEYPRESS('D'))
	{
		bBack = false;
		bMove = true;

		
		vLookDir = Vector3(vNextVector.x, transform->vPos.y, vNextVector.z) - transform->vPos;
		D3DXVec3Normalize(&vLookDir, &vLookDir);

		transform->vPos += vLookDir * (fSpeed * Et);

		if (transform->vPos.x > (vNextVector.x - 5.f))
		{
			if (iNowIndex != MAP->vWidthMap.size() - 1)
				++MAP->iWidthIndex;
		}
			
	}

	if (KEYDOWN(VK_SPACE))
	{
		if (bOnFloor)
		{
			bOnFloor = false;

			lpRigidBody->vVelocity.y = 0.f;
			lpRigidBody->AddForce(Vector3(0.f, 400, 0.));
		}
		else if (bDoubleJumpEnable && !bDoubleJump)
		{
			bDoubleJump = true;

			lpRigidBody->vVelocity.y = 0.f;
			lpRigidBody->AddForce(Vector3(0.f, 400, 0.));
		}
	}

	if (bMove)
	{
		if (bBack)
			GetLookAtS(transform->qRot, -vLookDir, 0.2f);
		else
			GetLookAtS(transform->qRot, vLookDir, 0.2f);

		lpAnimater->UnStop();
	}
}

void PlayerTank::Spawn()
{
	if (fSpawnElapsed >= fSpawnDelay)
	{
		fSpawnElapsed = 0.f;

		if (iLife > 0)
		{
			transform->vPos = vSpawnPos;
			SetState(PLAYERSTATE::E_PLAYERSTATE_IDLE);
		}
		else
			--iLife;
	}
	else
		fSpawnElapsed += Et;
}

void PlayerTank::Attack()
{
	if (KEYDOWN('1'))
		eWeapon = e_base;
	if (KEYDOWN('2'))
		eWeapon  = e_homming;
	if (KEYDOWN('3'))
		eWeapon = e_nuclear;


	if (KEYDOWN(VK_LBUTTON))
	{
		switch (eWeapon)
		{
		case e_base:
			AddObject(PlayerBullet)->SetBullet(E_PLAYERBULLET_01, transform->vPos + vWeaponFirePos, transform->qRot, 400.f, 1.f);
			lpGun->Attack();
			break;
		case e_homming:
			break;
		case e_nuclear:
			break;
		default:
			break;
		}
	}

}

void PlayerTank::SetTank(PLAYERTYPE etype)
{
	if (etype != eType)
	{
		eType = etype;

		switch (eType)
		{
		case e_none:
			break;
		case e_tank01:	
			vWeaponFirePos = Vector3(10.f, 20.f, 0.f);
			lpAnimater->Chanage(L"MovingA", 0.05f);
			lpPixelCollider->iHeight = 10;
			break;
		case e_tank02:
			vWeaponFirePos = Vector3(10.f, 20.f, 0.f);
			lpAnimater->Chanage(L"MovingA", 0.05f);
			lpPixelCollider->iHeight = 10;
			break;
		case e_tank03:
			vWeaponFirePos = Vector3(10.f, 20.f, 0.f);
			lpAnimater->Chanage(L"MovingA", 0.05f);
			lpPixelCollider->iHeight = 10;
			break;
		default:
			break;
		}
	}
}

void PlayerTank::SetState(PLAYERSTATE _eState)
{
	if (eState != _eState)
	{
		eState = _eState;

		switch (eState)
		{
		case E_PLAYERSTATE_DIE:
			break;
		case E_PLAYERSTATE_SPAWN:
			fSpawnElapsed = 0.f;

			lpRenderer->bEnable = false;
			lpCollider->bEnable = false;
			lpGun->bActive = false;

			fDoubleJumpElapsed = 0.f;
			bDoubleJumpEnable = false;

			fSpeedUpElapsed = 0.f;
			bSpeedUpEnable = false;

			iHommingCount = 0;
			iNuClearCount = 0;

			break;
		case E_PLAYERSTATE_IDLE:
			lpRenderer->bEnable = true;
			lpCollider->bEnable = true;
			lpGun->bActive = true;

			break;
		default:
			break;
		}
	}
}

void PlayerTank::ItemTimeCheck()
{
	if (bDoubleJumpEnable)
	{
		if (fDoubleJumpElapsed >= fDoubleJumpDelay)
		{
			fDoubleJumpElapsed = 0.f;
			bDoubleJumpEnable = false;
		}
		else
			fDoubleJumpElapsed += Et;
	}

	if (bSpeedUpEnable)
	{
		if (fSpeedUpElapsed >= fSpeedUpDelay)
		{
			fSpeedUpElapsed = 0.f;
			bSpeedUpEnable = false;
		}
		else
			fSpeedUpElapsed += Et;
	}
}

void PlayerTank::CameraSetting()
{
	Vector3 vOriginDir = Vector3(0.f, 0.f, 1.f);
	
	Vector3 vPivot = transform->vPos + Vector3(100.f, 0.f, 0.f);
	
	if (bBack)
		vPivot = transform->vPos + Vector3(-100.f, 0.f, 0.f);

	Quaternion qRot;
	D3DXQuaternionRotationMatrix(&qRot, &transform->matRot);

	D3DXQuaternionSlerp(&qCameraRot, &qCameraRot, &qRot, 0.1f);

	D3DXMATRIX matRot;
	D3DXMatrixRotationQuaternion(&matRot, &qCameraRot);

	D3DXVec3TransformNormal(&vOriginDir, &vOriginDir, &matRot);

	Vector3 vRight;
	D3DXVec3Cross(&vRight, &vOriginDir, &Vector3(0.f, 1.f, 0.f));

	Vector3 vTarget = vPivot +
		(-vRight) * 250.f;
	vTarget.y += 100.f;

	Vector3 vTargetLookAt = vPivot + Vector3(0.f, 50.f, 0.f);

	D3DXVec3Lerp(&lpCamera->vPos, &lpCamera->vPos, &vTarget, Et * 5);
	D3DXVec3Lerp(&lpCamera->vLookAt, &lpCamera->vLookAt, &vTargetLookAt, Et * 5);

	if (fShakeElapsed > fShakeDelay)
	{
		fShakeElapsed = 0.f;
		fShakeDelay = GetRandomNumber<float>(0.07, 0.1);

		if (bMove)
		{
			float power = GetRandomNumber<float>(-2.2, 2.2);

			lpCamera->vPos.y += (power);
			lpCamera->vLookAt.y += (power);

		}
	}
	else
		fShakeElapsed += Et;
}
