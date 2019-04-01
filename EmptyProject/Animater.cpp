#include "DXUT.h"
#include "Animater.h"


Animater::Animater()
{
}


Animater::~Animater()
{
}

void Animater::Init()
{
	gameObject->lpAnimater = this;
}

void Animater::Release()
{
	for (auto Iter : mAnimaters)
		SAFE_DELETE(Iter.second);
	mAnimaters.clear();

	if (gameObject->lpAnimater == this)
		gameObject->lpAnimater = nullptr;
}

void Animater::Update()
{
	if (bStop)
		return;

	if (!lpNowClip)
		return;

	if (!gameObject->lpRenderer)
		return;

	if (fElapsed >= fDelay)
	{
		fElapsed = 0.f;

		if (iCount < lpNowClip->veMehs.size() - 1)
		{
			++iCount;
		}
		else
		{
			iCount = 0;

			if (lpNowClip->endFunc)
				lpNowClip->endFunc();
		}

		gameObject->lpRenderer->lpMesh = lpNowClip->veMehs[iCount];
	}
	else
		fElapsed += Et();

}

void Animater::Add(RefStr id, RefStr keys, int min, int max, function<void()> _endFunc)
{
	if (auto find = mAnimaters.find(id); find != mAnimaters.end())
		return;

	AnimaterClip * lpClip = new AnimaterClip;
	LoadMeshs(lpClip->veMehs, keys, min, max);
	lpClip->endFunc = _endFunc;
	mAnimaters.insert(make_pair(id, lpClip));
}

void Animater::Chanage(RefStr id, float fS)
{
	if (auto find = mAnimaters.find(id); find != mAnimaters.end())
	{
		lpNowClip = find->second;

		fElapsed	= 0.f;
		fDelay		= fS;
		bStop		= false;

		if (gameObject->lpRenderer)
			gameObject->lpRenderer->lpMesh = lpNowClip->veMehs[0];
	}
	return;

}

void Animater::Stop(int _index)
{
	fElapsed = 0.f;
	bStop = true;
	iCount = _index;

	if (gameObject->lpRenderer)
		gameObject->lpRenderer->lpMesh = lpNowClip->veMehs[_index];
}

void Animater::UnStop()
{
	bStop = false;
}
