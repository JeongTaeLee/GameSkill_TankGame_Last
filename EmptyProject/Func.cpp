#include "DXUT.h"
#include "Func.h"
#include "ExplosionEffect.h"
void LoadTexs(RefStr keys, RefStr paths, int min, int max)
{
	for(int i = min; i <= max; ++i)
	{ 
		wchar_t key[256];
		swprintf(key, keys.c_str(), i);

		wchar_t path[256];
		swprintf(path, paths.c_str(), i);

		RESOURCE->AddTex(key, path);
	}
}

void LoadTexs(vector<texture*>& veTex, RefStr keys, int min, int max)
{
	for (int i = min; i <= max; ++i)
	{
		wchar_t key[256];
		swprintf(key, keys.c_str(), i);

		veTex.push_back(GetTex(key));
	}
}

void LoadMeshs(RefStr keys, RefStr paths, RefStr mtlName, int min, int max)
{
	for (int i = min; i <= max; ++i)
	{
		wchar_t key[256];
		swprintf(key, keys.c_str(), i);

		wchar_t path[256];
		swprintf(path, paths.c_str(), i);

		RESOURCE->AddMesh(key, path, mtlName);
	}
}

void LoadMeshs(vector<CMeshLoader*>& veTex, RefStr keys, int min, int max)
{
	for (int i = min; i <= max; ++i)
	{
		wchar_t key[256];
		swprintf(key, keys.c_str(), i);
		veTex.push_back(GetMesh_(key));
	}
}

void GetLookAt(Quaternion & qRot, const Vector3 & vDir)
{
	Matrix matRot;
	
	D3DXMatrixLookAtLH(&matRot, &Vector3(0.f, 0.f, 0.f), &vDir, &Vector3(0.f, 1.f, 0.f));
	D3DXMatrixTranspose(&matRot, &matRot);
	D3DXQuaternionRotationMatrix(&qRot, &matRot);

}

void GetLookAtS(Quaternion & qRot, const Vector3 & vDir, float _fS)
{
	Matrix matRot;

	D3DXMatrixLookAtLH(&matRot, &Vector3(0.f, 0.f, 0.f), &vDir, &Vector3(0.f, 1.f, 0.f));
	D3DXMatrixTranspose(&matRot, &matRot);
	
	D3DXQUATERNION _qRot;
	D3DXQuaternionRotationMatrix(&_qRot, &matRot);

	D3DXQuaternionSlerp(&qRot, &qRot, &_qRot, _fS);
	
}

void WorldTo2D(Vector3 & vResult, const Vector3 & vPos)
{
	if (vPos.x == 0 && vPos.y == 0 && vPos.z == 0)
	{
		vResult = Vector3(0.f, 0.f, 0.f);
		return;
	}

	D3DVIEWPORT9 vp;
	g_device->GetViewport(&vp);

	Matrix matViewProj = CAMERA->matView * CAMERA->matProj;
	
	Vector3 vSpaceToClient;
	D3DXVec3TransformCoord(&vSpaceToClient, &vPos, &matViewProj);

	vResult = Vector3(vp.Width * (vSpaceToClient.x + 1.0f) / 2.0f + vp.X,
		vp.Height * (2.f - (vSpaceToClient.y + 1.f)) / 2.f + vp.Y, 0.f);

}

void BillBoarding(Matrix & matWorld, RefV3 vPos, RefV3 vScale)
{
	matWorld = CAMERA->matView;
	memset(&matWorld._41, 0, sizeof(Vector3));
	D3DXMatrixInverse(&matWorld, nullptr, &matWorld);

	Vector3 vBillPos = vPos;
	memcpy(&matWorld._41, &vBillPos, sizeof(Vector3));
	
	Matrix matScale;
	D3DXMatrixScaling(&matScale, vScale.x, vScale.y, 1.f);

	matWorld = matScale * matWorld;
}

void CreateExplosionA(RefV3 vPos)
{
	ExplosionEffect * lpEffect = AddObject(ExplosionEffect);
	lpEffect->SetExplosion(L"BulletExplosion%d", 1, 41, 0.005f);
	float fSize = GetRandomNumber(20.f, 30.f);
	lpEffect->transform->vScale = Vector3(fSize, fSize, 1.f);
	lpEffect->transform->vPos = vPos;
}

void CreateExplosionB(RefV3 vPos)
{
	ExplosionEffect * lpEffect = AddObject(ExplosionEffect);
	lpEffect->SetExplosion(L"DieExplosionB%d", 1, 41, 0.005f);

	float fSize = GetRandomNumber(60.f, 70.f);
	lpEffect->transform->vScale = Vector3(fSize, fSize, 1.f);
	lpEffect->transform->vPos = vPos;
}

void CreateExplosionC(RefV3 vPos)
{
	ExplosionEffect * lpEffect = AddObject(ExplosionEffect);
	lpEffect->SetExplosion(L"DieExplosionB%d", 1, 41, 0.005f);

	float fSize = GetRandomNumber(60.f, 70.f);
	lpEffect->transform->vScale = Vector3(fSize, fSize, 1.f);
	lpEffect->transform->vPos = vPos;
}
