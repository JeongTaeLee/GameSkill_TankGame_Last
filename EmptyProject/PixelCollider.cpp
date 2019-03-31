#include "DXUT.h"
#include "PixelCollider.h"


PixelCollider::PixelCollider()
{
}


PixelCollider::~PixelCollider()
{
}

void PixelCollider::Init()
{
	gameObject->lpPixelCollider= this;
}

void PixelCollider::Release()
{
	if (gameObject->lpPixelCollider == this)
		gameObject->lpPixelCollider = nullptr;
}

void PixelCollider::Update()
{
	Vector3 vTempLeft = transform->vPos + vLeft;
	Vector3 vTempRight = transform->vPos + vRight;

	eCallTypeLeft = e_none;
	eCallTypeRight = e_none;
	
	bool bLeft = CheckHeight(vTempLeft, eCallTypeLeft);
	bool bRight = CheckHeight(vTempRight, eCallTypeRight);

	if (bLeft || bRight)
	{
		Vector3 vCenter = Vector3(0.f, 0.f, 0.f);
	
		D3DXVec3Lerp(&vCenter, &vTempLeft, &vTempRight, 0.5f);

		transform->vPos.y = vCenter.y;
		/*
		float fAngle = -D3DXToRadian(vTempRight.y - vTempLeft.y);

		Vector3 vDir(1.f, 0.f, 0.f);

		Matrix matRot;
		D3DXMatrixRotationQuaternion(&matRot, &transform->qRot);
		D3DXVec3TransformNormal(&vDir, &vDir, &matRot);

		Vector3 vRight(0.f, 0.f, 0.f);
		D3DXVec3Cross(&vRight, &vDir, &Vector3(0.f, 1.f, 0.f));
		
		Matrix matRightRot;
		D3DXMatrixRotationAxis(&matRightRot, &vRight, fAngle);

		matRot = matRightRot * matRot;
		D3DXQuaternionRotationMatrix(&transform->qRot, &matRot);
		*/

		
		if (funcCall)
			funcCall();
	}

}

bool PixelCollider::CheckHeight(Vector3 & vPos, PIXELTYPE & eType)
{
	int iWidth = MAP->iWidth;
	if (iWidth <= vPos.x && vPos.x < 0)
		return false;

	vector< pair<PIXELTYPE, int> > & pHeightMap = MAP->vHeightMap;

	pair<PIXELTYPE, int> Height = pHeightMap[(int)vPos.x];
	if (Height.second + iHeight> vPos.y)
	{
		vPos.y = Height.second + iHeight;

		eType = Height.first;
		return true;
	}

	return false;
}
