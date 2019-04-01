#include "DXUT.h"
#include "RankScreen.h"


RankScreen::RankScreen()
{
}


RankScreen::~RankScreen()
{
}

void RankScreen::Init()
{
	AC(UIRenderer);
	lpUIRenderer->lpTex = GetTex(L"RankScreen");
	transform->vPos = Vector3(319, 107, 0.f);

	Text * text;
	
	if(MAP->liScores.size() >= 0)
	{ 
		text = AC(Text);
		text->vPos = Vector3(257, 139, 0.f);

		wchar_t ch[256];
		swprintf(ch, L"%s, %d", MAP->liScores[0].first, MAP->liScores[0].second);
		text->str = ch;
	}
	
	if (MAP->liScores.size() > 1)
	{
		text = AC(Text);
		text->vPos = Vector3(257, 246, 0.f);
		wchar_t ch[256];
		swprintf(ch, L"%s, %d", MAP->liScores[1].first, MAP->liScores[1].second);
		text->str = ch;
	}

	if (MAP->liScores.size() > 2)
	{
		text = AC(Text);
		text->vPos = Vector3(257, 353, 0.f);
		wchar_t ch[256];
		swprintf(ch, L"%s, %d", MAP->liScores[2].first, MAP->liScores[2].second);
		text->str = ch;
	}

}
