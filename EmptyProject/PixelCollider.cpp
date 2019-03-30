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

	eCallType = e_none;
	
	bool bLeft = CheckHeight(vTempLeft);
	bool bRight = CheckHeight(vTempRight);

	if (bLeft || bRight)
	{
		Vector3 vCenter = Vector3(0.f, 0.f, 0.f);
	
		D3DXVec3Lerp(&vCenter, &vTempLeft, &vTempRight, 0.5f);

		transform->vPos.y = vCenter.y;
		transform->vRot.x = -D3DXToRadian(vTempRight.y - vTempLeft.y) * 10.f;

		switch (eCallType)
		{
		case e_red:
			if (funcRed)
				funcRed();
			break;
		case e_magenta:
			if (funcMagenta)
				funcMagenta();
				break;
		default:
			break;
		}
	}

}

bool PixelCollider::CheckHeight(Vector3 & vPos)
{
	int iWidth = MAP->iWidth;
	if (iWidth <= vPos.x && vPos.x < 0)
		return false;

	vector< pair<PIXELTYPE, int> > & pHeightMap = MAP->vHeightMap;

	pair<PIXELTYPE, int> Height = pHeightMap[(int)vPos.x];
	if (Height.second + iHeight> vPos.y)
	{
		vPos.y = Height.second + iHeight;

		if (Height.first == e_red)
			eCallType = e_red;
		if (Height.first == e_magenta)
			eCallType = e_magenta;

		return true;
	}

	return false;
}
