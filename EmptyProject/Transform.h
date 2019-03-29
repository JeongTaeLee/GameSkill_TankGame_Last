#pragma once
#include "Component.h"

enum TransformUpdateType
{
	TU_1,
	TU_2,
	TU_3,
};

class Transform :
	public Component
{
public:
	TransformUpdateType eType;

	Vector3 vWorldPos = Vector3(0.f, 0.f, 0.f);
	Vector3 vPos = Vector3(0.f, 0.f, 0.f);
	Vector3 vScale = Vector3(1.f, 1.f, 1.f);
	Vector3 vRot = Vector3(0.f, 0.f, 0.f);

	Quaternion qRot;
	Matrix matRot;
	Matrix matWorld;

public:
	GameObject * lpParent = nullptr;
	list<GameObject*> liAddChild;

public:
	Transform();
	virtual ~Transform();

	void TransformUpdate();

	void TransformUpdate01();
	void TransformUpdate02();
	void TransformUpdate03();

	GameObject * AddChild(GameObject * lpChild);
	void SetParent(GameObject * _lpParent) {  lpParent = _lpParent; }
	void DeleteChild(GameObject * child);
};


