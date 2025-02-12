#pragma once
#include "singleton.h"

class GameObject;
class Renderer;
class UIRenderer;
class Collider;
class BBRenderer;

class ObjectManager :
	public singleton<ObjectManager>
{
public:
	list<GameObject*> liGameObject;
	list<Renderer*> liRenderer;
	list<BBRenderer*> liBBRenderer;
	list<UIRenderer*> liUIRenderer;
	list<Collider*> liCollider;
public:
	ObjectManager();
	virtual ~ObjectManager();

	void Reset();


	template<class object>
	object * AddObject()
	{
		object * t = new object;

		liGameObject.push_back(t);
		t->Init();
		t->transform->TransformUpdate();

		return t;
	}

public:	
	Renderer * AddRenderer(Renderer * _renderer);
	UIRenderer * AddUIRenderer(UIRenderer * _renderer);
	BBRenderer * AddBBRenderer(BBRenderer * _lpBBRenderer);


	Collider * AddCollider(Collider * lpCollider);
	void  DeleteCollider(Collider * lpCollider);

	void DeleteRenderer(Renderer * _renderer);
	void DeleteBBRenderer(BBRenderer * lpBBRenderer);
	void DeleteUIRenderer(UIRenderer * _UIrenderer);

	void Update();
	void Render();
	
	void CollisionProcess();

};

#define OBJECT ObjectManager::Getinst()

#define AddObject(s) OBJECT->AddObject<##s##>()