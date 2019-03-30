#pragma once
#include "Component.h"

class CMeshLoader;

class Renderer:
	public Component
{
public:
	CMeshLoader * lpMesh = nullptr;

	function<void()> begin = nullptr;
	function<void()> end = nullptr;
public:
	Renderer();
	virtual ~Renderer();

	virtual void Init()	override;
	virtual void Release()	override;

	virtual void Render()	override;
};

