#include "AudioSystem.h"
#include "AudioSource.h"
#include <Windows.h>

// component ���
void AudioSystem::Regist(AudioSource* source)
{
	sources.push_back(source);
}

// component ��� ����
void AudioSystem::Unregist(AudioSource* source)
{
	// delete
	for (auto it = sources.begin(); it != sources.end(); ++it) {
		if (*it == source) {
			sources.erase(it);
			return;
		}
	}
}

void AudioSystem::Init()
{
	// fmod system
	FMOD_RESULT result = FMOD::System_Create(&system);
	if (result != FMOD_OK)
	{
		OutputDebugStringA("[Woo Engine] FMOD System ���� ����\n");
	}

	result = system->init(512, FMOD_INIT_NORMAL, nullptr);
	if (result != FMOD_OK)
	{
		OutputDebugStringA("[Woo Engine] FMOD System �ʱ�ȭ ����\n");
	}

	// channel grouping
	system->createChannelGroup("Master", &masterGroup);
	system->createChannelGroup("BGM", &bgmGroup);
	system->createChannelGroup("SFX", &sfxGroup);
	system->createChannelGroup("AMB", &ambGroup);

	masterGroup->addGroup(bgmGroup);
	masterGroup->addGroup(sfxGroup);
	masterGroup->addGroup(ambGroup);
}

void AudioSystem::Update()
{
	// system update
	if (system)
		system->update();
}

void AudioSystem::UnInit()
{
	if (system)
	{
		system->close();
		system->release();
		system = nullptr;
	}
}

void AudioSystem::SetMasterVolume(float volume)
{
	masterVolume = volume;

	if (masterGroup)
		masterGroup->setVolume(volume);
}

void AudioSystem::SetBGMVolume(float volume)
{
	bgmVolume = volume;

	if (bgmGroup)
		bgmGroup->setVolume(volume);
}

void AudioSystem::SetSFXVolume(float volume)
{
	sfxVolume = volume;

	if (sfxGroup)
		sfxGroup->setVolume(volume);
}

void AudioSystem::SetAMBVolume(float volume)
{
	ambVolume = volume;

	if (ambGroup)
		ambGroup->setVolume(volume);
}

float AudioSystem::GetMasterVolume()
{
	return masterVolume;
}

float AudioSystem::GetBGMVolume()
{
	return bgmVolume;
}

float AudioSystem::GetSFXVolume()
{
	return sfxVolume;
}

float AudioSystem::GetAMBVolume()
{
	return ambVolume;
}