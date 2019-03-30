#pragma once
#include "Component.h"

struct AnimaterClip
{
	vector<CMeshLoader*> veMehs;
	function< void() > endFunc = nullptr;
};

class Animater :
	public Component
{
public:
	map<wstring, AnimaterClip*> mAnimaters;

	AnimaterClip * lpNowClip = nullptr;

	int iCount = 0;

	float fElapsed = 0.f;
	float fDelay = 0.f;

	bool bStop = false;
public:
	Animater();
	virtual ~Animater();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Update()	override;


	void Add(RefStr id, RefStr keys, int min, int max, function< void() > _endFunc);
	void Chanage(RefStr id, float fS);
	void Stop(int _index);
	void UnStop();

};

