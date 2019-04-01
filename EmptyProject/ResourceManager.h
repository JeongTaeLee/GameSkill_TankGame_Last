#pragma once
#include "singleton.h"

struct Mesh;
class CMeshLoader;
class Material;

class ResourceManager :
	public singleton< ResourceManager>
{
public:
	map<wstring, texture*> mTexs;	
	map<wstring, CMeshLoader*> mMeshs;
	map<wstring, vector<Material*> * > mMaterial;
	map<wstring, LPD3DXEFFECT> mEffects;

	LPD3DXSPRITE lpSprite = nullptr;
	LPD3DXMESH lpMesh = nullptr;
public:
	ResourceManager();
	virtual ~ResourceManager();

	void Reset();

	texture * AddTex(RefStr key, RefStr path);
	void DestroyTex(RefStr key);

	CMeshLoader * AddMesh(RefStr key, RefStr path, RefStr mtlName = L"None");
	vector<Material*> * AddMaterial(RefStr key, RefStr path);

	LPD3DXEFFECT AddEffect(RefStr key, RefStr path);
};

#define RESOURCE ResourceManager::Getinst()

#define AdTex RESOURCE->AddTex	
#define AdMesh RESOURCE->AddMesh
#define AdEffect RESOURCE->AddEffect

#define GetTex(key) RESOURCE->AddTex(key, L"")
#define GetMesh_(key) RESOURCE->AddMesh(key, L"")
#define GetEffect(key) RESOURCE->AddEffect(key, L"")
