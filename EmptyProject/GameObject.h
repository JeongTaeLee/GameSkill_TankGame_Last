#pragma once

class Transform;
class Component;
class Collider;

class Text;
class Animater;
class Renderer;
class ShaderRenderer;
class UIRenderer;
class Collider;
class PixelCollider;
class RigidBody;
class BBRenderer;


class GameObject
{
public:
	string sTag = "None";

	Transform * transform = nullptr;

	bool bDestroy = false;
	bool bActive = true;
public:
	list<Component*> liComponent;

public:
	Text * lpText = nullptr;
	Renderer * lpRenderer = nullptr;
	ShaderRenderer * lpShaderRenderer = nullptr;
	UIRenderer * lpUIRenderer = nullptr;
	Animater * lpAnimater = nullptr;
	Collider * lpCollider = nullptr;
	PixelCollider * lpPixelCollider = nullptr;
	RigidBody * lpRigidBody = nullptr;
	BBRenderer * lpBBRenderer = nullptr;
public:
	GameObject();
	virtual ~GameObject();

	virtual void Init()	{}
	virtual void Release()	{}
	virtual void Update()	{}

	void ComUpdate();
public:
	virtual void ReceiveCollider(Collider * lpOther) {}
	void SendCollider(Collider * lpOther);

public:
	template <class T>
	T * AddComponent()
	{
		T * com = new T;

		liComponent.push_back(com);
		com->gameObject = this;
		com->transform = transform;
		com->Init();

		return com;
	}

	template <class T>
	T * GetComponent()
	{
		for (auto Iter : liComponent)
		{
			T * com = dynamic_cast<T*>(Iter);

			if (com)
				return com;
		}

		return nullptr;
	}
};

#define AC(Com) AddComponent<##Com##>()
#define GC(Com) GetComponent<##Com##>()