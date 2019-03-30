#include "DXUT.h"
#include "Func.h"

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

void LoadMeshs(RefStr keys, RefStr paths, int min, int max)
{
	for (int i = min; i <= max; ++i)
	{
		wchar_t key[256];
		swprintf(key, keys.c_str(), i);

		wchar_t path[256];
		swprintf(path, paths.c_str(), i);

		RESOURCE->AddMesh(key, path);
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
