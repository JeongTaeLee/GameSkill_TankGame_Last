#include "DXUT.h"
#include "PlayerTank.h"


PlayerTank::PlayerTank()
{
}


PlayerTank::~PlayerTank()
{
}

void PlayerTank::Init()
{
	transform->eType = TransformUpdateType::TU_2;

	transform->vScale = Vector3(0.4f, 0.4f, 0.4f);

	lpCamera = CAMERA->GetCamera(L"PlayerCamera");
	CAMERA->ChanageCamera(L"PlayerCamera");

	lpCamera->vPos = Vector3(0.f, 100.f, -150.f);

	AC(Renderer);
	AC(Animater);
	AC(RigidBody);
	AC(PixelCollider);

	lpAnimater->Add(L"Moving", L"TankA%d", 0, 1, [&]() { if (!bMove) lpAnimater->Stop(0); });
	lpAnimater->Chanage(L"Moving", 0.05f);

	lpRigidBody->bUseGravity = true;
	lpRigidBody->fMass = 2.3f;
	lpRigidBody->vDecrease.x = 0.94;
	lpRigidBody->vDecrease.z = 0.94;

	lpPixelCollider->iHeight = 6.f;

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
		break;
	case E_PLAYERSTATE_IDLE:
		Idle();

		break;
	}

	CameraSetting();
}

void PlayerTank::Idle()
{
	eMoveType = E_MOVE_NONE;

	float fSpeed = 100.f;

	int iNowIndex = MAP->iWidthIndex;
	int iNextIndex = iNowIndex + 1;

	Vector3 vNowVector = MAP->vWidthMap[iNowIndex];
	Vector3 vNextVector = MAP->vWidthMap[iNextIndex];

	if (KEYPRESS('A'))
	{
		eMoveType = E_MOVE_BACK;

		vLookDir = vNowVector - transform->vPos;
		D3DXVec3Normalize(&vLookDir, &vLookDir);
		vLookDir.y = 0.f;

		transform->vPos += vLookDir * (fSpeed * Et);

		if (transform->vPos.x < vNowVector.x)
		{
			if (iNowIndex == 0)
			{
			}
			else
			{
				iNowIndex = (--MAP->iWidthIndex);
				iNextIndex = iNowIndex + 1;

				vNowVector = MAP->vWidthMap[iNowIndex];
				vNextVector = MAP->vWidthMap[iNextIndex];
			}
		}
	}
	if (KEYPRESS('D'))
	{
		eMoveType = E_MOVE_FORWARD;

		vLookDir = vNextVector - transform->vPos;
		D3DXVec3Normalize(&vLookDir, &vLookDir);
		vLookDir.y = 0.f;

		transform->vPos += vLookDir * (fSpeed * Et);

		float fLength = GetLength(transform->vPos, vNextVector);

		if (transform->vPos.x > vNextVector.x)
		{
			if (iNowIndex == MAP->vWidthMap.size() - 2)
			{

			}
			else
			{
				iNowIndex = (++MAP->iWidthIndex);
				iNextIndex = iNowIndex + 1;

				vNowVector = MAP->vWidthMap[iNowIndex];
				vNextVector = MAP->vWidthMap[iNextIndex];
			}
		}
	}
	if (KEYDOWN(VK_SPACE))
	{
		lpRigidBody->vVelocity.y = 0.f;
		
		lpRigidBody->AddForce(Vector3(0.f, 400, 0.));
	}

	GetLookAtS(transform->qRot, vLookDir, 0.1f);

	if (eMoveType != E_MOVE_NONE)
		lpAnimater->UnStop();
}

void PlayerTank::CameraSetting()
{
	Vector3 vOriginDir = Vector3(0.f, 0.f, 1.f);
	D3DXVec3TransformNormal(&vOriginDir, &vOriginDir, &transform->matRot);
	Vector3 vT = transform->vPos + vOriginDir * 50.f;

	Vector3 vRight = Vector3(0.f, 0.f, 0.f);
	D3DXVec3Cross(&vRight, &vOriginDir, &Vector3(0.f, 1.f, 0.f));
	D3DXVec3Normalize(&vRight, &vRight);

	Vector3 vTarget = vT +
		(-vRight) * 220.f;
	vTarget.y += 120.f;

	Vector3 vLookAtTarget = vT +
		Vector3(0.f, 50.f, 0.f);

	D3DXVec3Lerp(&lpCamera->vPos, &lpCamera->vPos, &vTarget, Et * 3);
	D3DXVec3Lerp(&lpCamera->vLookAt, &lpCamera->vLookAt, &vLookAtTarget, Et * 3);

	if (fShakeElapsed > fShakeDelay)
	{
		fShakeElapsed = 0.f;
		fShakeDelay = GetRandomNumber<float>(0.07, 0.1);

		if (eMoveType != E_MOVE_NONE)
		{
			float power = GetRandomNumber<float>(-2.2, 2.2);

			lpCamera->vPos.y += (power);
			lpCamera->vLookAt.y += (power);

		}
	}
	else
		fShakeElapsed += Et;
}