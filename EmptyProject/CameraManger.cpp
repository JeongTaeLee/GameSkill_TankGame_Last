#include "DXUT.h"
#include "CameraManger.h"


CameraManger::CameraManger()
{
	AddCamera(L"BaseCamera");

	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(45.f), 16.f / 9.f, 1.f, 5000.f);
	g_device->SetTransform(D3DTS_PROJECTION, &matProj);
	SetViewMatrix();
}


CameraManger::~CameraManger()
{
	for (auto Iter : mCamers)
		SAFE_DELETE(Iter.second);

	mCamers.clear();
}

Camera * CameraManger::AddCamera(RefStr key)
{
	if (auto find = mCamers.find(key); find != mCamers.end())
		return find->second;

	return mCamers.insert(make_pair(key, new Camera)).first->second;
}

Camera * CameraManger::GetCamera(RefStr key)
{
	if (auto find = mCamers.find(key); find != mCamers.end())
		return find->second;

	return AddCamera(key);

}

Camera * CameraManger::GetCamera()
{
	return lpNowCamera;
}

Camera * CameraManger::ChanageCamera(RefStr key)
{
	if (auto find = mCamers.find(key); find != mCamers.end())
	{
		if (lpNowCamera)
		{
			find->second->vPos = lpNowCamera->vPos;
			find->second->vLookAt = lpNowCamera->vLookAt;
			find->second->vUP = lpNowCamera->vUP;
		}

		return (lpNowCamera = find->second);
	}

	return nullptr;
}

void CameraManger::Update()
{
	if (bShake)
	{
		if (lpNowCamera)
		{
			lpNowCamera->vPos.x += GetRandomNumber(-fPower, fPower);
			lpNowCamera->vPos.y += GetRandomNumber(-fPower, fPower);

			lpNowCamera->vLookAt.x += GetRandomNumber(-fPower, fPower);
			lpNowCamera->vLookAt.y += GetRandomNumber(-fPower, fPower);
		}

		if (fShakeElapsed >= fShakeDelay)
		{
			fShakeElapsed = 0.f;
			bShake = false;
		}
		else
			fShakeElapsed += Et;
	}
}

void CameraManger::SetViewMatrix()
{
	if (lpNowCamera)
	{
		D3DXMatrixLookAtLH(&matView, &lpNowCamera->vPos, &lpNowCamera->vLookAt, &lpNowCamera->vUP);
		g_device->SetTransform(D3DTS_VIEW, &matView);
	}
}

void CameraManger::SetShake(float _fPower, float _fShakeDelay)
{
	fPower = _fPower;
	fShakeDelay = _fShakeDelay;
	bShake = true;
}
