#pragma once
#include <string>
#include <fmod.hpp>

// mp3, wav ���� sound���� ���ҽ� asset
// Resource Manager�� ���ؼ� �����ؾ��մϴ�.

class AudioClip
{
private:
	FMOD::Sound* sound = nullptr;
	float length = 0.0f;

public:
	AudioClip(const std::string& filePath);
	~AudioClip();

	FMOD::Sound* GetSound() const { return sound; }
	bool IsValid() const { return sound != nullptr; }
	float GetLenght() { return length; }
};

