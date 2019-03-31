#include "DXUT.h"
#include "MonsterA.h"
#include "PlayerTank.h"

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
	lpCollider->SetCollider(25.f, Vector3(0.f, 0.f, 0.f));

	AC(RigidBody);

	funcState[E_IDLE] = [&]() { OnIdle(); };
	funcState[E_ATTACK] = [&]() { OnAttack(); };

	transform->vScale = Vector3(0.2f, 0.2f, 0.2f);
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

		lpRigidBody->AddForce(vDir * 6.f);
		GetLookAtS(transform->qRot, lpRigidBody->vDir, 0.2f);
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

		vDir = lpPlayer->transform->vPos - transform->vPos;
		D3DXVec3Normalize(&vDir, &vDir);
	}
	else
		fElapsed += Et;
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
		fElapsed += Et;
}

void MonsterA::SetMonsterA(MONSTERTYPE eType, RefV3 _vPos, RefV3 _vOffset)
{
	DEBUG_LOG("In");
	AC(ShaderRenderer);
	lpShaderRenderer->lpEffect = GetEffect(L"Lighting");

	switch (eType)
	{
	case E_MONSTERTYPE_1:
		lpShaderRenderer->lpMesh = GetMesh_(L"MonsterA1");
		break;
	case E_MONSTERTYPE_2:
		lpShaderRenderer->lpMesh = GetMesh_(L"MonsterA2");
		break;
	}
	transform->vPos = _vPos;
	vOffset			= _vOffset;

	eState = MONSTERASTATE::E_ATTACK;
	fElapsed = fDelay = 1.2f;
}


