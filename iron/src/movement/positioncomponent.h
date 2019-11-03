#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <math/vector.h>

ironBEGIN_NAMESPACE

class PositionComponent : public Component
{
public:
    PositionComponent(float x, float y) : m_Position(x, y), m_SizeX(1), m_SizeY(1) {}
	PositionComponent(float x, float y, int sizeX, int sizeY) : m_Position(x, y), m_SizeX(sizeX), m_SizeY(sizeY) {}

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