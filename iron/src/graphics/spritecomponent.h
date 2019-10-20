#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <SFML/Graphics.hpp>

ironBEGIN_NAMESPACE

class SpriteComponent : public Component
{
public:
	SpriteComponent(int spriteSheetX, int spriteSheetY) : m_SpriteSheetX(spriteSheetX), m_SpriteSheetY(spriteSheetY) {}
    const sf::Sprite& GetSprite() const { return m_Sprite; }
    sf::Sprite& GetSprite() { return m_Sprite; }
	int GetSpriteSheetX() const { return m_SpriteSheetX; }
	int GetSpriteSheetY() const { return m_SpriteSheetY; }

private:
    sf::Sprite m_Sprite;
	int m_SpriteSheetX;
	int m_SpriteSheetY;
};

ironEND_NAMESPACE