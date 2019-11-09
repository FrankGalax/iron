#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <math/vector.h>

ironBEGIN_NAMESPACE

class PositionComponent : public Component
{
public:
    PositionComponent(const Vector2f& position) : m_Position(position), m_SizeX(1), m_SizeY(1) {}
	PositionComponent(const Vector2f& position, int sizeX, int sizeY) : m_Position(position), m_SizeX(sizeX), m_SizeY(sizeY) {}

    Vector2f& GetPosition() { return m_Position; }
    const Vector2f& GetPosition() const { return m_Position; }
	int GetSizeX() const { return m_SizeX; }
	int GetSizeY() const { return m_SizeY; }

private:
    Vector2f m_Position;
	int m_SizeX;
	int m_SizeY;
};

ironEND_NAMESPACE