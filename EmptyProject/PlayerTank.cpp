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
	transform->vScale = Vector3(0.4f, 0.4f, 0.4f);

	lpCamera = CAMERA->GetCamera(L"PlayerCamera");
	CAMERA->ChanageCamera(L"PlayerCamera");

	lpCamera->vPos = Vector3(0.f, 100.f, -150.f);

	AC(Renderer);
	AC(Animater);

	lpAnimater->Add(L"Moving", L"TankA%d", 0, 1, [&]() { if (!bMove) lpAnimater->Stop(0); });
	lpAnimater->Chanage(L"Moving", 0.05f);
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
	bMove = false;
	float fSpeed = 200.f;

	Vector3 vNowDot = MAP->vWidthMap[MAP->iWidthIndex];
	Vector3 vNextDot = MAP->vWidthMap[MAP->iWidthIndex + 1];

	if (KEYPRESS('A'))
	{
		bMove = true;

		if (vNowDot.x < transform->vPos.x)
		{
			vLookDir = vNowDot - transform->vPos;
			D3DXVec3Normalize(&vLookDir, &vLookDir);

			transform->vPos += vLookDir * (fSpeed * Et);
			
			if (GetLength(transform->vPos, vNowDot) < 3.f)
			{
				if(MAP->iWidthIndex != 0)
					MAP->iWidthIndex--;
			}
		}
	}
	if (KEYPRESS('D'))
	{
		bMove = true;

		vLookDir = vNextDot - transform->vPos;
		D3DXVec3Normalize(&vLookDir, &vLookDir);

		transform->vPos += vLookDir * (fSpeed * Et);

		if (GetLength(transform->vPos, vNextDot) < 3.f)
		{

			if (MAP->iWidthIndex == MAP->vWidthMap.size() - 2)
			{
				//StageClear
			}
			else
				MAP->iWidthIndex++;
		}
	}

	if (bMove)
		lpAnimater->UnStop();

	Vector2 vRotDir = Vector2(vLookDir.x, vLookDir.z);
	transform->vRot.y = (-atan2f(vRotDir.y, vRotDir.x)) + D3DXToRadian(90.f);
}

void PlayerTank::CameraSetting()
{
	Vector3 vTarget =
		transform->vPos + Vector3(0.f, 100.f, -150.f);

	Vector3 vLookAtTaget =
		transform->vPos + Vector3(0.f, 50.f, 0.f);

	D3DXVec3Lerp(&lpCamera->vPos, &lpCamera->vPos, &vTarget, 0.4f);
	D3DXVec3Lerp(&lpCamera->vLookAt, &lpCamera->vLookAt, &vLookAtTaget, 0.4f);
}