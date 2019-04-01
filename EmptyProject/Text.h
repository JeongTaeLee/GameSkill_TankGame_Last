#pragma once
#include "UIRenderer.h"
class Text :
	public UIRenderer
{
public:
	wstring str = L"None";

	int iSize = 30;
public:
	Text();
	virtual ~Text();

	virtual void Init() override;
	virtual void Release()	override;
	virtual void Render()	override;

};

