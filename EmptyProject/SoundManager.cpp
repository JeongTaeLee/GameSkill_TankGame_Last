#include "DXUT.h"
#include "SoundManager.h"


SoundManager::SoundManager()
{
	pMgr = new CSoundManager;
	pMgr->Initialize(DXUTGetHWND(), 2);
}


SoundManager::~SoundManager()
{
	Clear();
	SAFE_DELETE(pMgr);

}

void SoundManager::AddSound(RefStr key, RefStr path)
{
	CSound* pSound;
	pMgr->Create(&pSound, (LPWSTR)path.c_str(), 0, GUID_NULL);

	mSounds.insert(make_pair(key, pSound));
}

void SoundManager::Play(RefStr key, bool isLoop, int v)
{
	mSounds[key]->GetBuffer(0)->SetVolume(v);
	mSounds[key]->GetBuffer(0)->Play(0, 0, isLoop);
}

void SoundManager::DuplicatePlay(RefStr key)
{
	LPDIRECTSOUNDBUFFER buf;

	pMgr->GetDirectSound()->DuplicateSoundBuffer(mSounds[key]->GetBuffer(0), &buf);

	buf->SetCurrentPosition(0);
	buf->Play(0, 0, 0);
}

void SoundManager::Stop(RefStr key)
{
	mSounds[key]->Stop();
}

void SoundManager::Clear()
{
	for (auto iter : mSounds)
	{
		SAFE_DELETE(iter.second);
	}
	mSounds.clear();
}
