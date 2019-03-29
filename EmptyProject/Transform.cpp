#include "DXUT.h"
#include "Transform.h"
#include "GameObject.h"

Transform::Transform()
{
	eType = TransformUpdateType::TU_1;

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matRot);
	D3DXQuaternionIdentity(&qRot);
}


Transform::~Transform()
{
	if (lpParent)
		lpParent->transform->DeleteChild(gameObject);

	for (auto Iter : liAddChild)
	{
		Iter->bDestroy = true;
		Iter->transform->SetParent(nullptr);
	}
	liAddChild.clear();
}

void Transform::TransformUpdate()
{
	switch (eType)
	{
	case TU_1:
		TransformUpdate01();
		break;
	case TU_2:
		TransformUpdate02();
		break;
	case TU_3:
		TransformUpdate03();
		break;
	default:
		break;
	}

	memcpy(&vWorldPos, &matWorld._41, sizeof(Vector3));
}

void Transform::TransformUpdate01()
{
	Matrix matScale;
	D3DXMatrixScaling(&matScale, vScale.x, vScale.y, vScale.z);

	D3DXQuaternionRotationYawPitchRoll(&qRot, vRot.y, vRot.x, vRot.z);
	D3DXMatrixRotationQuaternion(&matRot, &qRot);

	Matrix matPos;
	D3DXMatrixTranslation(&matPos, vPos.x, vPos.y, vPos.z);

	matWorld = matScale * matRot * matPos;

	if (lpParent)
		matWorld = matWorld * lpParent->transform->matWorld;
}

void Transform::TransformUpdate02()
{
	Matrix matScale;
	D3DXMatrixScaling(&matScale, vScale.x, vScale.y, vScale.z);

	D3DXMatrixRotationQuaternion(&matRot, &qRot);

	Matrix matPos;
	D3DXMatrixTranslation(&matPos, vPos.x, vPos.y, vPos.z);

	matWorld = matScale * matRot * matPos;

	if (lpParent)
		matWorld = matWorld * lpParent->transform->matWorld;
}

void Transform::TransformUpdate03()
{
	Matrix matScale;
	D3DXMatrixScaling(&matScale, vScale.x, vScale.y, 1.f);

	D3DXQuaternionRotationYawPitchRoll(&qRot, 0.f, 0.f, vRot.z);
	D3DXMatrixRotationQuaternion(&matRot, &qRot);

	Matrix matPos;
	D3DXMatrixTranslation(&matPos, vPos.x, vPos.y, 0.f);

	matWorld = matScale * matRot * matPos;

	if (lpParent)
		matWorld = matWorld * lpParent->transform->matWorld;
}

GameObject * Transform::AddChild(GameObject * lpChild)
{
	lpChild->transform->SetParent(gameObject);
	liAddChild.push_back(lpChild);
	return lpChild;
}

void Transform::DeleteChild(GameObject * child)
{
	child->transform->SetParent(nullptr);
	liAddChild.remove(child);
	child->bDestroy = true;
}


