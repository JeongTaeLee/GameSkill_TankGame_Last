#include "DXUT.h"
#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	if (lpNowScene)
		lpNowScene->Release();

	lpNowScene = nullptr;
	lpNextScene = nullptr;

	for (auto Iter : mScenes)
		SAFE_DELETE(Iter.second);
	mScenes.clear();
}

Scene * SceneManager::Add(RefStr key, Scene * _lpScene)
{
	if (auto find = mScenes.find(key); find != mScenes.end())
		return nullptr;

	return mScenes.insert(make_pair(key, _lpScene)).first->second;
}

Scene * SceneManager::ChangeScene(RefStr key)
{
	if (auto find = mScenes.find(key); find != mScenes.end())
	{
		sName		= find->first;
		lpNextScene = find->second;
	}

	return nullptr;
}

void SceneManager::Update()
{
	if (lpNextScene)
	{
		if (lpNowScene)
			lpNowScene->Release();
			
		lpNowScene = lpNextScene;
		lpNowScene->Init();
	}
	if (lpNowScene)
		lpNowScene->Update();
}
