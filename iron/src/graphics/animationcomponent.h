#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <vector>

ironBEGIN_NAMESPACE

struct AnimationSprite
{
    void SetSpriteSheetXY(int x, int y) { m_SpriteSheetX = x; m_SpriteSheetY = y; }
    int m_SpriteSheetX;
    int m_SpriteSheetY;
};

class AnimationComponent : public Component
{
public:
    std::vector<AnimationSprite>& GetAnimationSprites() { return m_AnimationSprites; }
    const std::vector<AnimationSprite>& GetAnimationSprites() const { return m_AnimationSprites; }
    float GetTime() const { return m_Time; }
    void SetTime(float time) { m_Time = time; }
    float GetTimer() const { return m_Timer; }
    void SetTimer(float timer) { m_Timer = timer; }
    int GetAnimationSpriteIndex() const { return m_AnimationSpriteIndex; }
    void SetAnimationSpriteIndex(int animationSpriteIndex) { m_AnimationSpriteIndex = animationSpriteIndex; }

private:
    std::vector<AnimationSprite> m_AnimationSprites;
    int m_AnimationSpriteIndex = 0;
    float m_Time = 0.f;
    float m_Timer = 0.f;
};

ironEND_NAMESPACE