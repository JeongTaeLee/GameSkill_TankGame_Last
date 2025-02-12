#include "DXUT.h"
#include "MonsterA.h"
#include "PlayerTank.h"
#include "MonsterBullet.h"

MonsterA::MonsterA()
{
}


MonsterA::~MonsterA()
{
}

void MonsterA::Init()
{
	Monster::Init();

	transform->eType = TransformUpdateType::TU_2;

	AC(Collider);
	lpCollider->SetCollider(20.f, Vector3(0.f, 10.f, 0.f));

	AC(RigidBody);

	funcState[E_IDLE] = [&]() { OnIdle(); };
	funcState[E_ATTACK] = [&]() { OnAttack(); };

	transform->vScale = Vector3(0.15f, 0.15f, 0.15f);
}

void MonsterA::Update()
{
	if (lpPlayer)
	{
		if (lpPlayer->bDestroy)
		{
			lpPlayer = nullptr;
			return;
		}

		funcState[eState]();

		lpRigidBody->AddForce(vDir * 5.f);
		GetLookAtS(transform->qRot, lpRigidBody->vDir, 0.2f);
		HommingCheck();
	}
	else
		return;
}

void MonsterA::OnAttack()
{
	if (fElapsed >= fDelay)
	{
		fElapsed = 0.f;
		fDelay = 1.f;
		
		eState = MONSTERASTATE::E_IDLE;

		Vector3 vPlayerDir = lpPlayer->transform->vPos - transform->vPos;
		D3DXVec3Normalize(&vPlayerDir, &vPlayerDir);
		
		AddObject(MonsterBullet)->SetBullet(transform->vPos, vPlayerDir, 5.f);

		vDir = lpPlayer->transform->vPos - transform->vPos;
		D3DXVec3Normalize(&vDir, &vDir);
	}
	else
		fElapsed += Et();
}

void MonsterA::OnIdle()
{
	if (fElapsed >= fDelay)
	{
		fElapsed = 0.f;
		fDelay = 1.f;
	
		eState = MONSTERASTATE::E_ATTACK;

		vDir = (lpPlayer->transform->vPos + vOffset) - transform->vPos;
		D3DXVec3Normalize(&vDir, &vDir);
	}
	else
		fElapsed += Et();
}

void MonsterA::SetMonsterA(MONSTERTYPE eType, RefV3 _vPos, RefV3 _vOffset)
{
	AC(ShaderRenderer);
	lpShaderRenderer->lpEffect = GetEffect(L"Lighting");

	eMonsterType = eType;

	switch (eMonsterType)
	{
	case E_MONSTERTYPE_A1:
		lpShaderRenderer->lpMesh = GetMesh_(L"MonsterA1");
		break;
	case E_MONSTERTYPE_A2:
		lpShaderRenderer->lpMesh = GetMesh_(L"MonsterA2");
		break;
	}
	transform->vPos = _vPos;
	vOffset			= _vOffset;

	eState = MONSTERASTATE::E_ATTACK;
	fElapsed = fDelay = 1.2f;
}


