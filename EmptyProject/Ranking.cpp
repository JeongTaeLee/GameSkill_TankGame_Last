#include "DXUT.h"
#include "Ranking.h"


Ranking::Ranking()
{
}


Ranking::~Ranking()
{
}

void Ranking::Init()
{
	transform->vPos = Vector3(375, 227, 0.f);

	AC(UIRenderer);
	lpUIRenderer->lpTex = GetTex(L"RankingInput");

	lpBastScore = AC(Text);
	lpName = AC(Text);
	lpScore = AC(Text);

	lpBastScore->iSize = lpName->iSize = lpScore->iSize = 36;

	lpBastScore->vPos = Vector3(301.f, 75.f, 0.f);
	lpName->vPos = Vector3(337.f, 126.f, 0.f);
	lpScore->vPos = Vector3(300.f, 177.f, 0.f);

	wchar_t str[7];
	swprintf(str, L"%06d", MAP->iScore);
	lpScore->str = str;

	int BastScore = MAP->GetBastScore();

	if (BastScore < MAP->iScore)
		BastScore = MAP->iScore;

	swprintf(str, L"%06d", BastScore);
	lpBastScore->str = str;

	lpName->str = L"";
}

void Ranking::Update()
{
	if (int i = INPUT->GetInputKey(); i != -1 && iCount < 3)
	{
		iCount++;
	
		wchar_t s = i;
		lpName->str += s;
	}
	
	if (iCount == 3)
	{
		if (KEYDOWN(VK_RETURN))
		{
			MAP->SaveScore(lpName->str, MAP->iScore);
			SCENE->ChangeScene(L"MainMenu");
		}
	}

}
