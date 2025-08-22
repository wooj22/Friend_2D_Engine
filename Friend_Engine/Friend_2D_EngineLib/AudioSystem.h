#pragma once
#include <fmod.hpp>
#include <vector>
#include "Singleton.h"
using namespace std;

/* AudioSystem�� ����
* 1. FMOD �ý��� �ʱ�ȭ �� ������Ʈ
* 2. masterGroup, bgmGroup, sfxGroup �⺻ ä�� �׷� ����
*/

class AudioSource;
class AudioSystem : public Singleton<AudioSystem>
{
private:
	// FMOD system
	FMOD::System* system = nullptr;			

	// channel group
	FMOD::ChannelGroup* masterGroup = nullptr;
	FMOD::ChannelGroup* bgmGroup = nullptr;
	FMOD::ChannelGroup* sfxGroup = nullptr;
	FMOD::ChannelGroup* ambGroup = nullptr;

	// channel vollune
	float masterVolume = 1.0f;
	float bgmVolume = 1.0f;
	float sfxVolume = 1.0f;
	float ambVolume = 1.0f;

private:
	vector<AudioSource*> sources;

public:
	// componenet
	void Regist(AudioSource* source);
	void Unregist(AudioSource* source);

	// component system
	void Init();
	void Update();
	void UnInit();

public:
	FMOD::System* GetSystem() const { return system; }

	FMOD::ChannelGroup* GetMasterGroup() const { return masterGroup; }
	FMOD::ChannelGroup* GetBGMGroup() const { return bgmGroup; }
	FMOD::ChannelGroup* GetSFXGroup() const { return sfxGroup; }
	FMOD::ChannelGroup* GetAMBGroup() const { return ambGroup; }

	void SetMasterVolume(float volume);
	void SetBGMVolume(float volume);
	void SetSFXVolume(float volume);
	void SetAMBVolume(float volume);

	float GetMasterVolume();
	float GetBGMVolume();
	float GetSFXVolume();
	float GetAMBVolume();
};

