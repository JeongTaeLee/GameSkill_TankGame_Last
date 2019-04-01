#include "DXUT.h"
#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
	D3DXCreateSprite(g_device, &lpSprite);
	
	D3DXCreateMeshFVF(2, 4, D3DXMESH_32BIT | D3DXMESH_MANAGED, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, g_device, &lpMesh);
	
	void * vp = nullptr;
	lpMesh->LockVertexBuffer(0, &vp);
	
	VERTEX * v = (VERTEX*)vp;

	v[0] = { Vector3(-1.f, 1.f, 0.f), Vector3(0.f, 0.f, 0.f), Vector2(0.f, 0.f) };
	v[1] = { Vector3(1.f, 1.f, 0.f), Vector3(0.f, 0.f, 0.f), Vector2(1.f, 0.f) };
	v[2] = { Vector3(1.f, -1.f, 0.f), Vector3(0.f, 0.f, 0.f), Vector2(1.f, 1.f) };
	v[3] = { Vector3(-1.f, -1.f, 0.f), Vector3(0.f, 0.f, 0.f), Vector2(0.f, 1.f) };

	lpMesh->UnlockVertexBuffer();

	void * ip = nullptr;
	lpMesh->LockIndexBuffer(0, &ip);

	DWORD * i = (DWORD*)ip;

	i[0] = 0; i[1] = 1; i[2] = 3; 
	i[3] = 3; i[4] = 1; i[5] = 2;

	lpMesh->UnlockIndexBuffer();
}


ResourceManager::~ResourceManager()
{	
	SAFE_RELEASE(lpSprite);
	SAFE_RELEASE(lpMesh);
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

CMeshLoader * ResourceManager::AddMesh(RefStr key, RefStr path)
{
	if (auto find = mMeshs.find(key); find != mMeshs.end())
		return find->second;

	CMeshLoader * loader = new CMeshLoader;
	loader->Create(path.c_str());

	return mMeshs.insert(make_pair(key, loader)).first->second;
}

LPD3DXEFFECT ResourceManager::AddEffect(RefStr key, RefStr path)
{
	if (auto find = mEffects.find(key); find != mEffects.end())
		return find->second;

	LPD3DXEFFECT lpEffect = nullptr;
	LPD3DXBUFFER lpBuffer = nullptr;
	DWORD dwFlag = D3DXSHADER_DEBUG;

#ifdef DEBUG
	dwFlag = D3DXSHADER_DEBUG;
#endif
	D3DXCreateEffectFromFileEx(g_device, path.c_str(), nullptr,
		nullptr, nullptr, dwFlag, nullptr, &lpEffect, &lpBuffer);

	if (!lpEffect && lpBuffer)
	{
		int size = lpBuffer->GetBufferSize();	
		void * buffer = lpBuffer->GetBufferPointer();

		if (buffer)
		{
			char * ch = new char[size];
			sprintf(ch, (char*)buffer);

			OutputDebugStringA(ch);
			DEBUG_LOG(ch);

			SAFE_DELETE_ARRAY(ch);
			return nullptr;
		}
	}

	return mEffects.insert(make_pair(key, lpEffect)).first->second;
}
