#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <graphics/spriteinfo.h>
#include <SFML/Graphics.hpp>

ironBEGIN_NAMESPACE

class UISpriteComponent : public Component
{
public:
    UISpriteComponent(int spriteSheetX, int spriteSheetY, float scaleX, float scaleY, int priority) : 
        m_SpriteSheetX(spriteSheetX), m_SpriteSheetY(spriteSheetY), m_ScaleX(scaleX), m_ScaleY(scaleY), m_Priority(priority) {}
    UISpriteComponent(const SpriteInfo& spriteInfo) :
        m_SpriteSheetX(spriteInfo.m_SpriteSheetX), m_SpriteSheetY(spriteInfo.m_SpriteSheetY), m_ScaleX(spriteInfo.m_ScaleX), 
        m_ScaleY(spriteInfo.m_ScaleY), m_Priority(spriteInfo.m_Priority) {}

    const sf::Sprite& GetSprite() const { return m_Sprite; }
    sf::Sprite& GetSprite() { return m_Sprite; }
    int GetSpriteSheetX() const { return m_SpriteSheetX; }
    void SetSpriteSheetX(int spriteSheetX) { m_SpriteSheetX = spriteSheetX; }
    int GetSpriteSheetY() const { return m_SpriteSheetY; }
    void SetSpriteSheetY(int spriteSheetY) { m_SpriteSheetY = spriteSheetY; }
    float GetScaleX() const { return m_ScaleX; }
    float GetScaleY() const { return m_ScaleY; }
    int GetPriority() const { return m_Priority; }

private:
    sf::Sprite m_Sprite;
    int m_SpriteSheetX = 0;
    int m_SpriteSheetY = 0;
    float m_ScaleX = 1.f;
    float m_ScaleY = 1.f;
    int m_Priority = 0;
};

ironEND_NAMESPACE