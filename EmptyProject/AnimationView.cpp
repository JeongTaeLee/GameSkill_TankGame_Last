#include "DXUT.h"
#include "AnimationView.h"


AnimationView::AnimationView()
{
}


AnimationView::~AnimationView()
{
}

void AnimationView::Update()
{
	if (bEnd)
		return;

	if (fElapsed >= 0.08f)
	{
		fElapsed = 0.f;

		if (iCount < veTex.size() - 1)
			iCount++;
		else
		{
			bool b = false;

			if (func)
				b = func();

			if (b)
				iCount = 0;
			else
				bEnd = true;
		}

		lpUIRenderer->lpTex = veTex[iCount];
	}
	else
		fElapsed += Et();

}

void AnimationView::SetAnimation(RefStr keys, int min, int max)
{
	LoadTexs(veTex, keys, min, max);
	
	AC(UIRenderer);
	lpUIRenderer->lpTex = veTex[0];
}
