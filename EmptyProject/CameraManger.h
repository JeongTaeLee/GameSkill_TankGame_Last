#pragma once
#include "singleton.h"

struct Camera
{
	Vector3 vPos = Vector3(0.f, 0.f, -10.f);
	Vector3 vLookAt = Vector3(0.f, 0.f, 0.f);
	Vector3 vUP = Vector3(0.f, 1.f, 0.f);
};

class CameraManger :
	public singleton < CameraManger >
{
public:
	map<wstring, Camera*> mCamers;

	Camera * lpNowCamera = nullptr;

	Matrix matView;
	Matrix matProj;
public:
	CameraManger();
	virtual ~CameraManger();

	Camera * AddCamera(RefStr key);
	Camera * GetCamera(RefStr key);
	Camera * GetCamera();

	Camera * ChanageCamera(RefStr key);

	void SetViewMatrix();
};

#define CAMERA CameraManger::Getinst()