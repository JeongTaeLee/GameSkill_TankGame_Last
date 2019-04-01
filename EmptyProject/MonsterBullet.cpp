#include "DXUT.h"
#include "MonsterBullet.h"


MonsterBullet::MonsterBullet()
{
	sTag = "MonsterBullet";
}


MonsterBullet::~MonsterBullet()
{
}

void MonsterBullet::Init()
{
	transform->vScale = Vector3(0.3f, 0.3f, 0.3f);

	AC(ShaderRenderer);
	lpShaderRenderer->lpEffect = GetEffect(L"Lighting");
	lpShaderRenderer->lpMesh = GetMesh_(L"MonsterBullet");

	AC(Collider);
	lpCollider->SetCollider(3.f, Vector3(0.f, 0.f, 0.f));

	AC(PixelCollider);
}

void MonsterBullet::Update()
{
	lpRigidBody->AddForce(vDir * fPower);

	if (fElapsed >= 1.3f)
	{
		CreateExplosionA(transform->vPos);
		bDestroy = true;
	}
	else
		fElapsed += Et();
}

void MonsterBullet::SetBullet(RefV3 vPos, RefV3 _vDir, float _fPower)
{
	transform->vPos = vPos;
	vDir = _vDir;
	fPower = _fPower;
	
	AC(RigidBody);
	lpRigidBody->AddForce(vDir * fPower);
}
