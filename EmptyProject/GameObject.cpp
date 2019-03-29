#include "DXUT.h"
#include "GameObject.h"
#include "Transform.h"
#include "Component.h"

GameObject::GameObject()
{
	transform = AC(Transform);
	transform->transform = transform;
}


GameObject::~GameObject()
{
	for (auto Iter : liComponent)
	{
		Iter->Release();
		SAFE_DELETE(Iter);
	}
	liComponent.clear();
}

void GameObject::ComUpdate()
{
	for (auto Iter : liComponent)
	{
		if (Iter->bEnable)
			Iter->Update();
	}
}

void GameObject::SendCollider(Collider * lpOther)
{
	ReceiveCollider(lpOther);

	for (auto Iter : liComponent)
		Iter->ReceiveCollider(lpOther);
}
