#pragma once
#include "singleton.h"

class Scene;

class SceneManager :
	public singleton<SceneManager>
{
public:
	map<wstring, Scene *> mScenes;

	Scene * lpNowScene = nullptr;
	Scene * lpNextScene = nullptr;

	wstring sName = L"None";
public:
	SceneManager();
	virtual ~SceneManager();

	Scene * Add(RefStr key, Scene * _lpScene);
	Scene * ChangeScene(RefStr key);

	void Update();


};

#define SCENE SceneManager::Getinst()

