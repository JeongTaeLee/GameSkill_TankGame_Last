#pragma once
#include "GameObject.h"
class PlayerHommingMissile :
	public GameObject
{
public:
	GameObject * lpTarget = nullptr;
public:
	PlayerHommingMissile();
	virtual ~PlayerHommingMissile();

	virtual void Init() override;
	virtual void Update()	override;

	void SetHomming(RefV3 vPos, GameObject * lpTarget);

	virtual void ReceiveCollider(Collider * lpOther) override;
};

