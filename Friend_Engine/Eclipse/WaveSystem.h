#pragma once
#include "../Friend_2D_EngineLib/Script.h"
#include <vector>
#include <random>
#include <cmath>

class GameObject;
class HonA;
class HonB; 
class HonC;
class HonD;
class Boss;
class GameManager;
class AudioSource;

enum class WaveState
{
    IDLE,
    WAVE_1,
    WAVE_2,
    WAVE_3,
    WAVE_BOSS,
    COMPLETED
};

struct SpawnData
{
    float x;
    float y;
    int honType; // 0: HonA, 1: HonB, 2: HonC, 3: HonD
    float delayTime;
};

class WaveSystem : public Script
{
public:
    WaveSystem();
    ~WaveSystem();

    void Awake() override;
    void Start() override;
    void Update() override;

    // Wave control
    void StartWave(int waveNumber);
    void StopWave();
    void ResetWaveSystem();
    
    // State getters
    WaveState GetCurrentWaveState() const;
    float GetWaveElapsedTime() const;
    int GetSpawnedCount() const;
    int GetDestroyedCount() const;
    bool IsWaveActive() const;
    
    // Hon destroyed callback
    void OnHonDestroyed(GameObject* hon);
    
private:
    // Wave state management
    WaveState m_currentWaveState;
    float m_waveElapsedTime;
    float m_waveDuration;
    
    // Spawn management
    std::vector<SpawnData> m_currentSpawnPattern;
    int m_currentSpawnIndex;
    float m_lastSpawnTime;
    int m_spawnedCount;
    int m_destroyedCount;
    
    // Active hons tracking
    std::vector<GameObject*> m_activeHons;
    GameObject* m_activeBoss;
    bool m_isUpdatingHons = false;
    
    // Random generator
    std::mt19937 m_randomGen;
    std::uniform_real_distribution<float> m_xDistribution;
    
    // GameManager reference
    GameManager* m_gameManager;

    // Audio
    AudioSource* m_waveEndAudioSource;

    // Wave StartCheck
	bool m_waveStartCheck = true;

    // Spawn parameters
    static constexpr float SPAWN_Y = 900.0f;  // 맵 위쪽에서 스폰 (맵 높이 1920의 약 상단)
    static constexpr float BOSS_SPAWN_Y = 900.0f;
    static constexpr float HUN_SIZE = 128.0f;
    static constexpr float BOSS_SIZE = 512.0f;
    static constexpr float SPAWN_MARGIN = 256.0f;
    static constexpr float FALL_TIME = 15.0f;
    static constexpr float BOSS_FALL_TIME = 80.0f;
    
    // Wave pattern setup
    void SetupWave1Pattern();
    void SetupWave2Pattern();
    void SetupWave3Pattern();
    void SetupBossPattern();
    
    // Helper functions for spawn collision checking
    bool IsSpawnPositionSafeForABC(float x, float y, const std::vector<SpawnData>& existingHonDSpawns, float currentTime);
    static constexpr float MIN_DISTANCE_FROM_HOND = 300.0f; // Minimum distance to avoid accidental collisions
    
    // Spawn functions
    void SpawnHon(int honType, float x, float y);
    void SpawnBoss();
    
    // Spawn position calculation
    float GetRandomSpawnX();
    float GetSpawnY(bool isBoss = false);
};