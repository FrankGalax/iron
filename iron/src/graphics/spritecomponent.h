#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <graphics/spriteinfo.h>
#include <SFML/Graphics.hpp>

ironBEGIN_NAMESPACE

class SpriteComponent : public Component
{
public:
    SpriteComponent(int spriteSheetX, int spriteSheetY, float scaleX, float scaleY) :
        m_SpriteSheetX(spriteSheetX), m_SpriteSheetY(spriteSheetY), m_ScaleX(scaleX), m_ScaleY(scaleY) {}
    SpriteComponent(const SpriteInfo& spriteInfo) :
        m_SpriteSheetX(spriteInfo.m_SpriteSheetX), m_SpriteSheetY(spriteInfo.m_SpriteSheetY), m_ScaleX(spriteInfo.m_ScaleX), m_ScaleY(spriteInfo.m_ScaleY) {}

    const sf::Sprite& GetSprite() const { return m_Sprite; }
    sf::Sprite& GetSprite() { return m_Sprite; }
    int GetSpriteSheetX() const { return m_SpriteSheetX; }
    void SetSpriteSheetX(int spriteSheetX) { m_SpriteSheetX = spriteSheetX; }
    int GetSpriteSheetY() const { return m_SpriteSheetY; }
    void SetSpriteSheetY(int spriteSheetY) { m_SpriteSheetY = spriteSheetY; }
    float GetScaleX() const { return m_ScaleX; }
    float GetScaleY() const { return m_ScaleY; }

private:
    sf::Sprite m_Sprite;
    int m_SpriteSheetX;
    int m_SpriteSheetY;
    float m_ScaleX;
    float m_ScaleY;
};

ironEND_NAMESPACE