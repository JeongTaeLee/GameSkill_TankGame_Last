#include "DXUT.h"
#include "PlayerTank.h"
#include "PlayerBullet.h"
#include "PlayerGun.h"
#include "PlayerNuClear.h"
#include "PlayerUI.h"
#include "MosnterDieEffect.h"
#include "PlayerDieEffect.h"
#include "PlayerHommingMissile.h"
#include "GameClear.h"
#include "GameOver.h"
Vector3 PlayerTank::vSpawnPos = Vector3(0.f, 0.f, 0.f);

PlayerTank::PlayerTank()
{
	sTag = "Player";

	D3DXQuaternionIdentity(&qCameraRot);
}


PlayerTank::~PlayerTank()
{
}

void PlayerTank::Init()
{
	transform->eType = TransformUpdateType::TU_2;
	transform->vScale = Vector3(0.2f, 0.2f, 0.2f);

	lpGun = AddObject(PlayerGun);
	transform->AddChild(lpGun);

	lpPlayerUI = AddObject(PlayerUI);

	lpCamera = CAMERA->GetCamera(L"PlayerCamera");
	CAMERA->ChanageCamera(L"PlayerCamera");

	lpCamera->vPos = Vector3(0.f, 100.f, -150.f);

	AC(ShaderRenderer);
	lpShaderRenderer->lpEffect = GetEffect(L"Lighting");
	
	AC(Collider);
	lpCollider->SetCollider(10.f, Vector3(0.f, 0.f, 0.f));

	AC(Animater);
	lpAnimater->Add(L"MovingA", L"PlayerA%d", 0, 1, [&]() { if (!bMove) lpAnimater->Stop(0); });
	lpAnimater->Add(L"MovingB", L"PlayerB%d", 0, 1, [&]() { if (!bMove) lpAnimater->Stop(0); });
	lpAnimater->Add(L"MovingC", L"PlayerC%d", 0, 1, [&]() { if (!bMove) lpAnimater->Stop(0); });
	AC(RigidBody);
	lpRigidBody->bUseGravity = true;
	lpRigidBody->fMass = 1.6f;
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
			if (eState == E_PLAYERSTATE_IDLE && !bLifeInfinity)
				SetState(E_PLAYERSTATE_SPAWN);
		}
	};
	SetTank(e_tank01);

	lpPlayerUI->SetWeapon(PLAYERWEAPON::e_base, 0);
	lpPlayerUI->SetNuClear(iNuClearCount);
	lpPlayerUI->AddScore(0);
	lpPlayerUI->SetLife(iLife);
}

void PlayerTank::Release()
{
	lpPlayerUI->bDestroy = true;
}

void PlayerTank::Update()
{
	if (KEYDOWN(VK_F1))
		bLifeInfinity = !bLifeInfinity;

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

	case E_PLAYERSTATE_NUCLEAR:
		if (fNuClearElapsed >= fNuClearDelay)
		{
			fNuClearElapsed = 0.f;
			SetState(E_PLAYERSTATE_IDLE);
		}
		else
			fNuClearElapsed += Et();
		break;

	}

	ShaderRenderer::vLight = transform->vPos + Vector3(0.f, 100.f, 0.f);

	CameraSetting();
}

void PlayerTank::ReceiveCollider(Collider * lpOther)
{
	if (lpOther->gameObject->sTag == "Stone")
	{
		if (eState == E_PLAYERSTATE_IDLE && !bLifeInfinity)
			SetState(E_PLAYERSTATE_SPAWN);
	}

	if (lpOther->gameObject->sTag == "MonsterBullet" && !bLifeInfinity)
	{
		if (eState == E_PLAYERSTATE_IDLE)
			SetState(E_PLAYERSTATE_SPAWN);
	}
}

void PlayerTank::Idle()
{
	float fSpeed = 12.0f;
	bMove = false;

	int iNowIndex = MAP->iWidthIndex;
	int iNextIndex = iNowIndex + 1;

	Vector3 vNowVector = MAP->vWidthMap[iNowIndex];
	Vector3 vNextVector = MAP->vWidthMap[iNextIndex];

	if (KEYPRESS('A'))
	{
		fTotalSpeed -= fSpeed;
		bMove = true;
	}
	if (KEYPRESS('D'))
	{
		fTotalSpeed += fSpeed;
		bMove = true;
	}

	if (fTotalSpeed > 0.f)
	{
		bBack = false;

		vLookDir = Vector3(vNextVector.x, transform->vPos.y, vNextVector.z) - transform->vPos;
		D3DXVec3Normalize(&vLookDir, &vLookDir);
		
		if (transform->vPos.x > (vNextVector.x - 5.f))
		{
			if (iNowIndex != MAP->vWidthMap.size() - 1)
				++MAP->iWidthIndex;
			else
			{
				fTotalSpeed = 0.f;

				if (!bGameEnd)
				{
					bGameEnd = true;
					AddObject(GameClear);
				}
			}
		}
	}
	else if (fTotalSpeed < 0.f)
	{
		bBack = true;
		bMove = true;

		vLookDir = Vector3(vNowVector.x, transform->vPos.y, vNowVector.z) - transform->vPos;
		D3DXVec3Normalize(&vLookDir, &vLookDir);

		if (transform->vPos.x < (vNowVector.x + 5.f))
		{
			if (iNowIndex != 0)
				--MAP->iWidthIndex;
		}
	}

	if (bBack)
		transform->vPos += -vLookDir * (fTotalSpeed * Et());
	else
		transform->vPos += vLookDir * (fTotalSpeed * Et());
	fTotalSpeed *= 0.92;

	if (KEYDOWN(VK_SPACE))
	{
		if (bOnFloor)
		{
			bOnFloor = false;

			lpRigidBody->vVelocity.y = 0.f;
			lpRigidBody->AddForce(Vector3(0.f, 300, 0.));
		}
		else if (bDoubleJumpEnable && !bDoubleJump)
		{
			bDoubleJump = true;

			lpRigidBody->vVelocity.y = 0.f;
			lpRigidBody->AddForce(Vector3(0.f, 200, 0.));
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

		--iLife;
		lpPlayerUI->SetLife(iLife);

		if (iLife > 0)
		{
			transform->vPos = vSpawnPos;
			SetState(PLAYERSTATE::E_PLAYERSTATE_IDLE);
		}
		else
		{
			AddObject(GameOver);
			SetState(PLAYERSTATE::E_PLAYERSTATE_DIE);
		}
	}
	else
		fSpawnElapsed += Et();
}

void PlayerTank::Attack()
{
	if (KEYDOWN('1'))
	{
		eWeapon = e_base;
		lpPlayerUI->SetWeapon(PLAYERWEAPON::e_base, 0);
	}
	if (KEYDOWN('2'))
	{
		eWeapon  = e_homming;
		lpPlayerUI->SetWeapon(PLAYERWEAPON::e_homming, iHommingCount);
	}
	if (KEYDOWN('3'))
	{
		eWeapon = e_nuclear;
		lpPlayerUI->SetWeapon(PLAYERWEAPON::e_nuclear, iNuClearCount);
	}
	if (KEYDOWN('V'))
		AddObject(MosnterDieEffect)->SetMonsterDieEffect(MONSTERTYPE::E_MONSTERTYPE_A1, transform->vPos, Vector3(0.2f, 0.2f, 0.2f));

	if (KEYDOWN(VK_F2))
	{
		SetUpgrad();
	}
	if (KEYDOWN(VK_F3))
	{
		if ((int)eType > 0)
		{
			PLAYERTYPE _eType = (PLAYERTYPE)((int)eType - 1);
			SetTank(_eType);
		}
	}

	if (KEYDOWN(VK_LBUTTON))
	{
		SOUND->DuplicatePlay(L"Fire");

		switch (eWeapon)
		{
		case e_base:
		{
			AddObject(PlayerBullet)->SetBullet(E_PLAYERBULLET_01, transform->vPos + vWeaponFirePos, transform->qRot, 400.f, 1.f);
			lpGun->Attack(vRight, bNwayBulletEnable);
			break;
		}
		case e_homming:
			lpPlayerUI->SetWeapon(PLAYERWEAPON::e_homming, iHommingCount);
			break;
		case e_nuclear:
			if (iNuClearCount > 0)
			{
				--iNuClearCount;

				SetState(PLAYERSTATE::E_PLAYERSTATE_NUCLEAR);
				AddObject(PlayerNuClear)->transform->vPos = Vector3(transform->vPos.x,
					transform->vPos.y + 600.f, transform->vPos.z);

				lpPlayerUI->SetWeapon(PLAYERWEAPON::e_nuclear, iNuClearCount);
				lpPlayerUI->SetNuClear(iNuClearCount);
			}
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
			lpGun->SetGun(PLAYERGUNTYPE::e_gun01);
			vWeaponFirePos = Vector3(10.f, 10.f, 0.f);
			lpAnimater->Chanage(L"MovingA", 0.05f);
			lpPixelCollider->iHeight = 10;
			break;
		case e_tank02:
			lpGun->SetGun(PLAYERGUNTYPE::e_gun02);
			vWeaponFirePos = Vector3(10.f, 10.f, 0.f);
			lpAnimater->Chanage(L"MovingB", 0.05f);
			lpPixelCollider->iHeight = 10;
			break;
		case e_tank03:
			lpGun->SetGun(PLAYERGUNTYPE::e_gun03);
			vWeaponFirePos = Vector3(10.f, 10.f, 0.f);
			lpAnimater->Chanage(L"MovingC", 0.05f);
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

			fRangeUpElapsed = 0.f;
			bRangeUpEnable = false;

			fNwayBulletElapsed = 0.f;
			bNwayBulletEnable = false;

			iHommingCount = 0;
			iNuClearCount = 0;

			eWeapon = PLAYERWEAPON::e_base;
			lpPlayerUI->SetWeapon(e_base, 0);

			lpPlayerUI->SetLife(iLife);
			lpPlayerUI->SetNuClear(iNuClearCount);
			lpPlayerUI->SetDoubleJump(false);
			lpPlayerUI->SetRangeUp(false);
			lpPlayerUI->SetNwayBullet(false);
			
			AddObject(PlayerDieEffect)->SetPlayerDieEffect(eType, transform->vPos);
			break;
		case E_PLAYERSTATE_IDLE:
			CAMERA->ChanageCamera(L"PlayerCamera");
			lpRenderer->bEnable = true;
			lpCollider->bEnable = true;
			lpGun->bActive = true;

			break;
		case E_PLAYERSTATE_NUCLEAR:
			fNuClearElapsed = 0.f;
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
			lpPlayerUI->SetDoubleJump(false);
		}
		else
			fDoubleJumpElapsed += Et();
	}

	if (bNwayBulletEnable)
	{
		if (fNwayBulletElapsed >= fNwayBulletDelay)
		{
			fNwayBulletElapsed= 0.f;
			bNwayBulletEnable = false;
			lpPlayerUI->SetNwayBullet(false);
		}
		else
			fNwayBulletElapsed += Et();
	}

	if (bRangeUpEnable)
	{
		if (fRangeUpElapsed >= fRangeUpDelay)
		{
			fRangeUpElapsed = 0.f;
			bRangeUpEnable = false;
			lpPlayerUI->SetRangeUp(false);
		}
		else
			fRangeUpElapsed += Et();
	}
}

void PlayerTank::CameraSetting()
{
	Camera * camere = nullptr;
	camere = lpCamera;
	
	Vector3 vPivot = transform->vPos + Vector3(50.f, 0.f, 0.f);
	
	Quaternion qRot;
	D3DXQuaternionRotationMatrix(&qRot, &transform->matRot);
	D3DXQuaternionSlerp(&qCameraRot, &qCameraRot, &qRot, 0.1f);

	D3DXMATRIX matRot;
	Vector3 vOriginDir = Vector3(0.f, 0.f, 1.f);
	D3DXMatrixRotationQuaternion(&matRot, &qCameraRot);
	D3DXVec3TransformNormal(&vOriginDir, &vOriginDir, &matRot);
	D3DXVec3Cross(&vRight, &vOriginDir, &Vector3(0.f, 1.f, 0.f));
	
	Vector3 vTarget = Vector3(0.f, 0.f, 0.f);
	Vector3 vTargetLookAt = Vector3(0.f, 0.f, 0.f);

	
	vTarget = vPivot + (-vRight) * 150.f;
	vTarget.y += 50.f;
	vTargetLookAt = vPivot + Vector3(0.f, 30.f, 0.f);
	

	D3DXVec3Lerp(&camere->vPos, &camere->vPos, &vTarget, Et() * 5);
	D3DXVec3Lerp(&camere->vLookAt, &camere->vLookAt, &vTargetLookAt, Et() * 5);

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
		fShakeElapsed += Et();
}

void PlayerTank::SetDoubleJump()
{
	bDoubleJumpEnable = true;
	fDoubleJumpElapsed = 0.f;
	lpPlayerUI->SetDoubleJump(true);
}

void PlayerTank::SetSpeedUp()
{
	bSpeedUpEnable = true;
	lpPlayerUI->SetSpeedUp(true);
}

void PlayerTank::SetUpgrad()
{
	if ((int)eType < (int)e_tank03)
	{
		PLAYERTYPE _eType = (PLAYERTYPE)((int)eType + 1);
		SetTank(_eType);
	}
}

void PlayerTank::SetRangeUp()
{
	bRangeUpEnable = true;
	bRangeUpEnable = 0.f;
	lpPlayerUI->SetRangeUp(true);
}

void PlayerTank::SetNwayBullet()
{
	bNwayBulletEnable = true;
	fNwayBulletElapsed = 0.f;
	lpPlayerUI->SetNwayBullet(true);
}

void PlayerTank::AddNuClear()
{
	if (iNuClearCount < 2)
	{
		++iNuClearCount;

		if (eWeapon == e_nuclear)
			lpPlayerUI->SetWeapon(e_nuclear, iNuClearCount);
	}
}

void PlayerTank::AddHomming()
{
	++iHommingCount;

	if (eWeapon == e_homming)
		lpPlayerUI->SetWeapon(e_homming, iHommingCount);
}

void PlayerTank::FireHommingMissile(GameObject * lpTank)
{
	if (eWeapon == e_homming && iHommingCount > 0)
	{
		iHommingCount--;
		lpPlayerUI->SetWeapon(e_homming, iHommingCount);
		AddObject(PlayerHommingMissile)->SetHomming(transform->vPos, lpTank);
	}
}
