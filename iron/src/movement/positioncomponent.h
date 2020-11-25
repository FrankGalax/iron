#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <math/vector.h>

ironBEGIN_NAMESPACE

class PositionComponent : public Component
{
public:
    PositionComponent(const Vector2f& position) : m_Position(position), m_Size(1.f, 1.f) {}
	PositionComponent(const Vector2f& position, const Vector2f& size) : m_Position(position), m_Size(size) {}

    Vector2f& GetPosition() { return m_Position; }
    const Vector2f& GetPosition() const { return m_Position; }
    const Vector2f& GetSize() const { return m_Size; }

private:
    Vector2f m_Position;
	Vector2f m_Size;
};

ironEND_NAMESPACE