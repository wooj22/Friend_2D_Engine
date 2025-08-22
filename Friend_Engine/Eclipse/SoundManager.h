#pragma once
#include "../Direct2D_EngineLib/AudioSystem.h"
#include "../Direct2D_EngineLib/Script.h"
#include "../Direct2D_EngineLib/Time.h"

#include <algorithm>

template<typename T>
T Clamp(T value, T minVal, T maxVal)
{
    if (value < minVal) return minVal;
    if (value > maxVal) return maxVal;
    return value;
}

class SoundManager : public Script
{
private:
    float deltaTime;

    float masterVolume = 1.0f;
    float bgmVolume = 1.0f;
    float sfxVolume = 1.0f;
    float ambVolume = 1.0f;

    float bgmScale = 1.0f;
    float bgmBaseScale = 0.5f;   // ���� BGM Ŀ�� �⺻���� ���̴� ��


private:
    void ApplyVolumes()
    {
        AudioSystem::Get().SetMasterVolume(masterVolume);

        // bgmVolume�� 0~1 ���� ����, ���� ��� ���� ��� �ø� ����
        float finalBGM = Clamp(bgmVolume, 0.0f, 1.0f) * bgmScale * bgmBaseScale;
        AudioSystem::Get().SetBGMVolume(finalBGM);
        AudioSystem::Get().SetSFXVolume(sfxVolume);
        AudioSystem::Get().SetAMBVolume(ambVolume);
    }

    struct FadeInfo
    {
        float start = 1.0f;      // ���̵� ���� ���� ����
        float target = 1.0f;
        float duration = 0.0f;
        float elapsed = 0.0f;
        bool active = false;
    };

    FadeInfo masterFade;

public:

    SoundManager() = default;
    ~SoundManager() = default;

    void Update()
    {
        if (!masterFade.active) return;

        float deltaTime = Time::GetDeltaTime();
        masterFade.elapsed += deltaTime;

        float t = (((masterFade.elapsed / masterFade.duration) < (1.0f)) ? (masterFade.elapsed / masterFade.duration) : (1.0f));
        masterVolume = masterFade.start + t * (masterFade.target - masterFade.start);

        ApplyVolumes();

        if (t >= 1.0f) masterFade.active = false;
    }

    // ���� ���� (�ɼ�â���� ����ϴ� ��)
    void SetMasterVolume(float volume) { masterVolume = Clamp(volume, 0.0f, 1.0f); ApplyVolumes(); }
    void SetBGMVolume(float volume) { bgmVolume = Clamp(volume, 0.0f, 1.0f); ApplyVolumes(); }
    void SetSFXVolume(float volume) { sfxVolume = Clamp(volume, 0.0f, 1.0f); ApplyVolumes(); }
    void SetAMBVolume(float volume) { ambVolume = Clamp(volume, 0.0f, 1.0f); ApplyVolumes(); }

    // ���� �ɼ� ���� 
    float GetMasterVolume() const { return masterVolume; }
    float GetBGMVolume() const { return bgmVolume; }
    float GetSFXVolume() const { return sfxVolume; }
    float GetAMBVolume() const { return ambVolume; }

    // BGM ������
    void SetBGMScale(float scale) { bgmScale = Clamp(scale, 0.0f, 1.0f); ApplyVolumes(); }
    float GetBGMScale() const { return bgmScale; }

    float GetFinalBGMVolume() const
    {
        return Clamp(bgmVolume, 0.0f, 1.0f) * bgmScale * bgmBaseScale;
    }

    // [ ���̵� ��/�ƿ� ]
    void FadeMaster(float targetVolume, float duration)
    {
        masterFade.start = masterVolume;        // ���� ���� ���
        masterFade.target = Clamp(targetVolume, 0.0f, 1.0f);
        masterFade.duration = duration;
        masterFade.elapsed = 0.0f;
        masterFade.active = true;
    }

    // ���̵� ��: ������ ������ 1�� ���� �ø�
    void FadeInMaster(float duration) { FadeMaster(1.0f, duration); }

    // ���̵� �ƿ�: ������ ������ 0���� ���� ����
    void FadeOutMaster(float duration) { FadeMaster(0.0f, duration); }
};