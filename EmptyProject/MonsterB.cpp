#include "DXUT.h"
#include "MonsterB.h"
#include "PlayerTank.h"

MonsterB::MonsterB()
{
	iLife = 5;
}


MonsterB::~MonsterB()
{
}

void MonsterB::Init()
{
	Monster::Init();

	transform->eType = TransformUpdateType::TU_2;

	AC(Collider);
	lpCollider->SetCollider(30.f, Vector3(0.f, 0.f, 0.f));

	AC(RigidBody);

	funcState[E_IDLE] = [&]() { OnIdle(); };
	funcState[E_ATTACK] = [&]() { OnAttack(); };

	transform->vScale = Vector3(0.3f, 0.3f, 0.3f);
}

void MonsterB::Update()
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
		//GetLookAtS(transform->qRot, lpRigidBody->vDir, 0.2f);

		transform->vRot.y += D3DXToRadian(2.f);
	}
	else
		return;
}

void MonsterB::OnAttack()
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

void MonsterB::OnIdle()
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

void MonsterB::SetMonsterB(MONSTERTYPE eType, RefV3 _vPos, RefV3 _vOffset)
{
	AC(ShaderRenderer);
	lpShaderRenderer->lpEffect = GetEffect(L"Lighting");

	eMonsterType = eType;

	switch (eMonsterType)
	{
	case E_MONSTERTYPE_B1:
		lpShaderRenderer->lpMesh = GetMesh_(L"MonsterB1");
		break;
	case E_MONSTERTYPE_B2:
		lpShaderRenderer->lpMesh = GetMesh_(L"MonsterB2");
		break;
	}
	transform->vPos = _vPos;
	vOffset = _vOffset;

	eState = MONSTERASTATE::E_ATTACK;
	fElapsed = fDelay = 1.2f;
}
