#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <math/vector.h>

ironBEGIN_NAMESPACE

class JSON;

class PositionComponent : public Component
{
public:
    PositionComponent() {}
    PositionComponent(const Vector2f& position) : m_Position(position), m_Size(1.0f, 1.0f) {}
    PositionComponent(const Vector2f& position, const Vector2f& size) : m_Position(position), m_Size(size) {}

    Vector2f& GetPosition() { return m_Position; }
    const Vector2f& GetPosition() const { return m_Position; }
    const Vector2f& GetSize() const { return m_Size; }

    virtual void ToJSON(JSON* j) override;

private:
    Vector2f m_Position;
    Vector2f m_Size;
};

ironEND_NAMESPACE