#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <SFML/Graphics.hpp>

ironBEGIN_NAMESPACE

class SpriteComponent : public Component
{
public:
    const sf::Sprite& GetSprite() const { return m_Sprite; }
    sf::Sprite& GetSprite() { return m_Sprite; }

private:
    sf::Sprite m_Sprite;
};

ironEND_NAMESPACE