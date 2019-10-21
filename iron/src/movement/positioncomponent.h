#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <math/vector.h>

ironBEGIN_NAMESPACE

class PositionComponent : public Component
{
public:
	typedef Component super;
	PositionComponent(float x, float y) : super(), m_Position(x, y) {}

    Vector2f& GetPosition() { return m_Position; }
    const Vector2f& GetPosition() const { return m_Position; }

private:
    Vector2f m_Position;
};

ironEND_NAMESPACE