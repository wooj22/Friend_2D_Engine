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

/* [AnimationClip]
* json파일을 읽어와 Texture2D에서 여러 Sprite를 생성하고 프레임 정보를 저장하는 클래스
* 게임 콘텐츠에서는 이 클래스를 상속받은 자식 클래스에서 
* textrue정보와 json data(sprite sheet, animation clip)로 frames를 생성하도록 미리 Asset을 정의한다.
* Animator에서는 미리 정의한 Clip 클래스의 객체를 생성시킨다.
* ex) class PlayerRunClip : public AnimationClip{}
*/

struct AnimationFrame
{
    shared_ptr<Sprite> sprite;      // sprite
    float time = 0.0f;              // start timing
};

class AnimationClip
{
public:
    string name;                     // animation clip name
    float duration = 1.0f;           // 재생 시간
    bool loop = true;                // 반복 여부
    vector<AnimationFrame> frames;   // sprite, time data   

public:
    AnimationClip() = default;
    virtual ~AnimationClip() = default;

public:
    void LoadSpritesFromJson(shared_ptr<Texture2D> texture, const string& jsonPath);
    void LoadAnimationClipFromJson(shared_ptr<Texture2D> texture, const string& jsonPath);
};