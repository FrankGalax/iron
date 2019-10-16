#pragma once

#include <iron.h>
#include <ecs/component.h>

ironBEGIN_NAMESPACE

class PositionComponent : public Component
{
public:
	typedef Component super;
	PositionComponent(float x, float y) : super(), m_X(x), m_Y(y) {}

	void SetX(float x) { m_X = x; }
	float GetX() const { return m_X; }
	void SetY(float y) { m_Y = y; }
	float GetY() const { return m_Y; }

private:
	float m_X;
	float m_Y;
};

ironEND_NAMESPACE