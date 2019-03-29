#include "DXUT.h"
#include "ResourceManager.h"
#include "MeshLoader.h"


ResourceManager::ResourceManager()
{
	D3DXCreateSprite(g_device, &lpSprite);
	
	D3DXCreateMeshFVF(2, 4, D3DXMESH_32BIT | D3DXMESH_MANAGED, MYFVF, g_device, &lpMesh);
	
	void * vp = nullptr;
	lpMesh->LockVertexBuffer(0, &vp);
	
	VERTEX * v = (VERTEX*)vp;

	v[0] = { Vector3(-1.f, 1.f, 0.f), Vector3(0.f, 0.f, 0.f), Vector2(0.f, 0.f) };
	v[1] = { Vector3(1.f, 1.f, 0.f), Vector3(0.f, 0.f, 0.f), Vector2(1.f, 0.f) };
	v[2] = { Vector3(1.f, -1.f, 0.f), Vector3(0.f, 0.f, 0.f), Vector2(0.f, 1.f) };
	v[3] = { Vector3(-1.f, -1.f, 0.f), Vector3(0.f, 0.f, 0.f), Vector2(1.f, 1.f) };

	lpMesh->UnlockVertexBuffer();

	void * ip = nullptr;
	lpMesh->LockIndexBuffer(0, &ip);

	DWORD * i = (DWORD*)ip;

	i[0] = 0; i[1] = 1; i[2] = 3; 
	i[3] = 3; i[4] = 1; i[5] = 2;

	lpMesh->UnlockIndexBuffer();

	lpLoader = new MeshLoader;
}


ResourceManager::~ResourceManager()
{	
	SAFE_RELEASE(lpSprite);
	SAFE_RELEASE(lpMesh);
	SAFE_DELETE(lpLoader);

	Reset();
}

void ResourceManager::Reset()
{

	for (auto Iter : mTexs)
		SAFE_DELETE(Iter.second);
	mTexs.clear();

	for (auto Iter : mMeshs)
		SAFE_DELETE(Iter.second);
	mMeshs.clear();

	for (auto Iter : mEffects)
		SAFE_RELEASE(Iter.second);
	mEffects.clear();
}

texture * ResourceManager::AddTex(RefStr key, RefStr path)
{
	if (auto find = mTexs.find(key); find != mTexs.end())
		return find->second;

	LPDIRECT3DTEXTURE9 lpTex = nullptr;
	D3DXIMAGE_INFO info;

	if(FAILED(D3DXCreateTextureFromFileEx(g_device, path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, nullptr, &lpTex)))
	{
		DEBUG_LOGW(L"Failed Loading Image : " << key << " path : " << path);
		return nullptr;
	}
		
	return mTexs.insert(make_pair(key, new texture(lpTex, info))).first->second;
}

void ResourceManager::DestroyTex(RefStr key)
{
	if (auto find = mTexs.find(key); find != mTexs.end())
	{
		SAFE_DELETE(find->second);
		mTexs.erase(find);
	}
}

Mesh * ResourceManager::AddMesh(RefStr key, RefStr path)
{
	if (auto find = mMeshs.find(key); find != mMeshs.end())
		return find->second;

	Mesh * lpMesh = new Mesh;

	if (FAILED(lpLoader->Create(lpMesh, path.c_str())))
	{
		DEBUG_LOGW(L"LFailed Mesh Load : " << key << L" , " <<  path);
		return nullptr;
	}

	return mMeshs.insert(make_pair(key, lpMesh)).first->second;
}

LPD3DXEFFECT ResourceManager::AddEffect(RefStr key, RefStr path)
{
	if (auto find = mEffects.find(key); find != mEffects.end())
		return find->second;

	LPD3DXEFFECT lpEffect = nullptr;
	LPD3DXBUFFER lpBuffer = nullptr;
	DWORD dwFlag = 0;

#ifdef DEBUG
	dwFlag = D3DXSHADER_DEBUG;
#endif
	D3DXCreateEffectFromFileEx(g_device, key.c_str(), nullptr,
		nullptr, nullptr, dwFlag, nullptr, &lpEffect, &lpBuffer);

	if (!lpEffect && lpBuffer)
	{
		int size = lpBuffer->GetBufferSize();	
		void * buffer = lpBuffer->GetBufferPointer();

		if (buffer)
		{
			wchar_t * st = new wchar_t[size];
			swprintf(st, (wchar_t*)buffer);

			OutputDebugString(st);
			DEBUG_LOGW(st);

			SAFE_DELETE_ARRAY(st);
			return nullptr;
		}
	}

	return mEffects.insert(make_pair(key, lpEffect)).first->second;
}
