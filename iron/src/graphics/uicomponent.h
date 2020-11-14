#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <SFML/Graphics.hpp>

ironBEGIN_NAMESPACE

class UIComponent : public Component
{
public:
	sf::Sprite& GetBorderRight() { return m_BorderRight; }
	sf::Sprite& GetBorderTopRight() { return m_BorderTopRight; }
	sf::Sprite& GetBorderTop() { return m_BorderTop; }
	sf::Sprite& GetBorderTopLeft() { return m_BorderTopLeft; }
	sf::Sprite& GetBorderLeft() { return m_BorderLeft; }
	sf::Sprite& GetBorderBottomLeft() { return m_BorderBottomLeft; }
	sf::Sprite& GetBorderBottom() { return m_BorderBottom; }
	sf::Sprite& GetBorderBottomRight() { return m_BorderBottomRight; }
	sf::Sprite& GetInventoryBackground() { return m_InventoryBackground; }
	std::vector<sf::Sprite*>& GetInventorySprites() { return m_InventorySprites; }

private:
	sf::Sprite m_BorderRight;
	sf::Sprite m_BorderTopRight;
	sf::Sprite m_BorderTop;
	sf::Sprite m_BorderTopLeft;
	sf::Sprite m_BorderLeft;
	sf::Sprite m_BorderBottomLeft;
	sf::Sprite m_BorderBottom;
	sf::Sprite m_BorderBottomRight;
	sf::Sprite m_InventoryBackground;
	std::vector<sf::Sprite*> m_InventorySprites;
};

ironEND_NAMESPACE