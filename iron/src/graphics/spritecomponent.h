#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <SFML/Graphics.hpp>

ironBEGIN_NAMESPACE

class SpriteComponent : public Component
{
public:
    SpriteComponent(int spriteSheetX, int spriteSheetY, float scaleX, float scaleY) :
        m_SpriteSheetX(spriteSheetX), m_SpriteSheetY(spriteSheetY), m_ScaleX(scaleX), m_ScaleY(scaleY) {}

    const sf::Sprite& GetSprite() const { return m_Sprite; }
    sf::Sprite& GetSprite() { return m_Sprite; }
    int GetSpriteSheetX() const { return m_SpriteSheetX; }
    int GetSpriteSheetY() const { return m_SpriteSheetY; }
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