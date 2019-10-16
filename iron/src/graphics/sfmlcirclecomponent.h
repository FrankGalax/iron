#pragma once

#include <iron.h>
#include <SFML/Graphics.hpp>
#include <ecs/component.h>

ironBEGIN_NAMESPACE

class SFMLCircleComponent : public Component
{
public:
	typedef Component super;
	SFMLCircleComponent(float radius) : super(), m_CircleShape(radius) {}

	const sf::CircleShape& GetCircleShape() const { return m_CircleShape; }
	sf::CircleShape& GetCircleShape() { return m_CircleShape; }
private:
	sf::CircleShape m_CircleShape;
};

ironEND_NAMESPACE