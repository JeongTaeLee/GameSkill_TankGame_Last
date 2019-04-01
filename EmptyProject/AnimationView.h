#pragma once
#include "GameObject.h"
class AnimationView :
	public GameObject
{
public:
	vector<texture*> veTex;

	float fElapsed = 0.f;
	int iCount = 0;

	bool bEnd = false;

	function <bool()> func = nullptr;
public:
	AnimationView();
	virtual ~AnimationView();

	virtual void Update()	override;
	void SetAnimation(RefStr keys, int min, int max);
};

