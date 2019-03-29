#pragma once
#include "Component.h"

class Renderer:
	public Component
{
public:
	Mesh * lpMesh = nullptr;

	function<void()> begin = nullptr;
	function<void()> end = nullptr;
public:
	Renderer();
	virtual ~Renderer();

	virtual void Init()	override;
	virtual void Release()	override;

	virtual void Render()	override;
};

