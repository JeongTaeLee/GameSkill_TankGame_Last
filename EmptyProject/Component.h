#pragma once

class Transform;
class GameObject;
class Collider;

class Component
{
public:
	GameObject * gameObject = nullptr;
	Transform * transform = nullptr;

	bool bEnable = true;
public:
	Component();
	virtual ~Component();

	virtual void Init() { }
	virtual void Release() { }
	virtual void Update() { } 
	virtual void Render() { }

public:
	virtual void ReceiveCollider(Collider * lpOther) {};
};

