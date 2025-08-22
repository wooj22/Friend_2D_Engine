#pragma once
#include <fmod.hpp>
#include "AudioClip.h"
#include "AudioSystem.h"
#include "Component.h"
#include <iostream>

/* [AudioSource Component]
* ������ AudioClip�� ����� �� �ִ� ������Ʈ�̴�. 
* �ϳ��� channel�� ������, ���� ������ ��ø ����� �Ұ����ϴ�.
* channel�� �ٸ� ä�� �׷쿡 ��ϵǾ� ����� �ͽ� ����� Ȱ���� �� �ִ�.
* Clip�� ���ҽ��Ŵ����� �����Ǿ� shared_ptr<AudioClip>���� ��ȴ�.
*/

class AudioSource : public Component
{
private:
    FMOD::System* system = nullptr;             // fmod sound system
    shared_ptr<AudioClip> clip = nullptr;       // �� audiosource�� ����� audioClip
    FMOD::Channel* channel = nullptr;           // sound�� ��µ� channel

    // channel output group
    FMOD::ChannelGroup* outputChannel = nullptr;

    // audoi source data
    float volume = 1.0;
    bool isLoop = false;

public:
    // component cycle
    AudioSource() { system = AudioSystem::Get().GetSystem(); }
    ~AudioSource() override = default;

    void OnEnable_Inner() override final;
    void OnDisable_Inner() override final;
    void OnDestroy_Inner() override final;

public:
    // functions
    void SetClip(shared_ptr<AudioClip> newClip);
    void SetVolume(float volume);
    float GetVolume();
    void SetLoop(bool loop);
    bool GetLoop();
    float GetCurrentClipLenght();
    float GetCurrentPlayTime();     // sound play ����� 0.0 ~ 1.0
    float GetPlaybackProgress();
    void Play();
    void PlayOneShot();
    void Stop();
    bool IsPlaying() const;

    // group
    void SetChannelGroup(FMOD::ChannelGroup* channelGroup);
    FMOD::ChannelGroup* GetChannelGroup();
};

