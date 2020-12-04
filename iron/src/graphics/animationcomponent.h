#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <vector>

#pragma region usercode
#include <graphics/animationsprite.h>
#pragma endregion

ironBEGIN_NAMESPACE

class JSON;

class AnimationComponent : public Component
{
public:
    AnimationComponent() {}
    std::vector<AnimationSprite>& GetAnimationSprites() { return m_AnimationSprites; }
    const std::vector<AnimationSprite>& GetAnimationSprites() const { return m_AnimationSprites; }
    int GetAnimationSpriteIndex() const { return m_AnimationSpriteIndex; }
    void SetAnimationSpriteIndex(int animationSpriteIndex) { m_AnimationSpriteIndex = animationSpriteIndex; }
    float GetTime() const { return m_Time; }
    void SetTime(float time) { m_Time = time; }
    float GetTimer() const { return m_Timer; }
    void SetTimer(float timer) { m_Timer = timer; }

    virtual void ToJSON(JSON* j) override;

private:
    std::vector<AnimationSprite> m_AnimationSprites;
    int m_AnimationSpriteIndex = 0;
    float m_Time = 0.f;
    float m_Timer = 0.f;
};

ironEND_NAMESPACE