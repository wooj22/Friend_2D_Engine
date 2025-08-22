#pragma once
#include "../Direct2D_EngineLib/json.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <memory>
#include "Sprite.h"
#include "Texture2D.h"
#include "ResourceManager.h"
using namespace std;

/* [AnimationClip Asset]
* json������ �о�� Texture2D���� ���� Sprite�� �����ϰ� ������ ������ �����ϴ� Ŭ����
* ���� ������������ �� Ŭ������ ��ӹ��� �ڽ� Ŭ�������� 
* textrue������ json data(sprite sheet, animation clip)�� frames�� �����ϵ��� �̸� Asset�� �����Ѵ�.
* ex) class PlayerRunClip : public AnimationClip{} -> �� Ŭ���� Ŭ������ ���� �ʿ�� ���� �ڵ�θ� �����ص� �ȴ�.
*/

struct AnimationFrame
{
    shared_ptr<Sprite> sprite;      // sprite
    float time = 0.0f;              // start timing
};

// TODO :: ���ҽ� �Ŵ����� �����ϱ�
class AnimationClip
{
public:
    string name;                     // animation clip name
    float duration = 1.0f;           // ��� �ð�
    bool loop = true;                // �ݺ� ����
    vector<AnimationFrame> frames;   // sprite, time data

private:
    std::vector<shared_ptr<Sprite>> spritesList;    // sprite sheet ���� ������

public:
    AnimationClip() = default;
    virtual ~AnimationClip() = default;

public:
    void LoadSpriteSheetFromJson(shared_ptr<Texture2D> texture, const string& jsonPath);
    void LoadAnimationClipFromJson(shared_ptr<Texture2D> texture, const string& jsonPath);

    int GetFrameIndexAtTime(float time);
};