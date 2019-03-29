#pragma once
#include "Renderer.h"
class ShaderRenderer :
	public Renderer
{
public :
	LPD3DXEFFECT lpEffect = nullptr;
public:
	ShaderRenderer();
	virtual ~ShaderRenderer();

	virtual void Init()	override;
	virtual void Release()	override;

	virtual void Render()	override;

};

