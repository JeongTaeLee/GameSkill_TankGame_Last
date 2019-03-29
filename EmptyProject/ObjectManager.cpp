#include "DXUT.h"
#include "ObjectManager.h"

#include "GameObject.h"
#include "Transform.h"
#include "Component.h"
#include "UIRenderer.h"
#include "Renderer.h"
ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

void ObjectManager::Reset()
{
	for (auto Iter : liGameObject)
	{
		Iter->Release();
		SAFE_DELETE(Iter);
	}
	liGameObject.clear();
}

Renderer * ObjectManager::AddRenderer(Renderer * _renderer)
{
	liRenderer.push_back(_renderer);
	return _renderer;
}

UIRenderer * ObjectManager::AddUIRenderer(UIRenderer * _renderer)
{
	liUIRenderer.push_back(_renderer);
	return _renderer;
}

void ObjectManager::DeleteRenderer(Renderer * _renderer)
{
	liRenderer.remove(_renderer);
}

void ObjectManager::DeleteUIRenderer(UIRenderer * _UIrenderer)
{
	liUIRenderer.remove(_UIrenderer);
}

void ObjectManager::Update()
{
	for (auto Iter = liGameObject.begin(); Iter != liGameObject.end();)
	{
		if ((*Iter)->bDestroy)
		{
			(*Iter)->Release();
			SAFE_DELETE((*Iter));
			Iter = liGameObject.erase(Iter);
		}
		else
		{
			if ((*Iter)->bActive)
			{
				(*Iter)->Update();
				(*Iter)->ComUpdate();
				(*Iter)->transform->TransformUpdate();
			}

			++Iter;	
		}
	}

	CollisionProcess();
}

void ObjectManager::Render()
{
	for (auto Iter : liRenderer)
	{
		if (Iter->bEnable)
			Iter->Render();
	}

	RESOURCE->lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	for (auto Iter : liUIRenderer)
	{
		if (Iter->bEnable)
			Iter->Render();
	}

	RESOURCE->lpSprite->End();

}

void ObjectManager::CollisionProcess()
{

}
