#pragma once
#include "singleton.h"
#include "SDKsound.h"


class SoundManager :
	public singleton< SoundManager >
{
private:
	CSoundManager * pMgr = nullptr;

	map<wstring, CSound*> mSounds;
public:
	SoundManager();
	virtual ~SoundManager();

	void AddSound(RefStr key, RefStr path);
	void Play(RefStr key, bool isLoop = false, int v = 0);
	void DuplicatePlay(RefStr key);
	void Stop(RefStr key);
	void Clear();

};

#define SOUND SoundManager::Getinst()