#pragma once
#include "Renderer.h"
class BBRenderer :
	public Renderer
{
public:

	texture * lpEffectTex = nullptr;
public:
	BBRenderer();
	virtual ~BBRenderer();
	
	virtual void Init() override;
	virtual void Release()	override;

	virtual void Render() override;

};

