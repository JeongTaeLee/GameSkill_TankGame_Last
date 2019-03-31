#include "DXUT.h"
#include "ObjectManager.h"

#include "GameObject.h"
#include "Transform.h"
#include "Component.h"
#include "UIRenderer.h"
#include "Renderer.h"
#include "Collider.h"

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

Collider * ObjectManager::AddCollider(Collider * lpCollider)
{
	liCollider.push_back(lpCollider);
	return lpCollider;
}

void ObjectManager::DeleteCollider(Collider * lpCollider)
{
	liCollider.remove(lpCollider);
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
	for (auto Iter01 : liCollider)
	{
		if (Iter01->gameObject->bDestroy)
			continue;

		if (!Iter01->gameObject->bActive)
			continue;

		if (!Iter01->bEnable)
			continue;		

		for (auto Iter02 : liCollider)
		{
			if (Iter01 == Iter02)
				continue;

			if (Iter02->gameObject->bDestroy)
				continue;

			if (!Iter02->gameObject->bActive)
				continue;

			if (!Iter02->bEnable)
				continue;

			float fRad01 = Iter01->fRad;
			float fRad02 = Iter02->fRad;

			Vector3 vOffset01 = Iter01->GetOffset();
			Vector3 vOffset02 = Iter02->GetOffset();

			if ((fRad01 + fRad02) > GetLength(vOffset01, vOffset02))
			{
				Iter01->OnCollider(Iter02);
				Iter02->OnCollider(Iter01);
				continue;
			}
		}
	}

}
