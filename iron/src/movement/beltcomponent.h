#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <math/vector.h>

ironBEGIN_NAMESPACE

class BeltComponent : public Component
{
public:
    const BeltComponent* GetNextBelt() const { return m_NextBelt; }
    void SetNextBelt(BeltComponent* nextBelt) { m_NextBelt = nextBelt; }
    float GetSpeed() const { return m_Speed; }
    const Vector2f& GetDirection() const { return m_Direction; }
    void SetDirection(const Vector2f& direction) { m_Direction = direction; }

private:
    BeltComponent* m_NextBelt = nullptr;
    float m_Speed = 1.0f;
    Vector2f m_Direction;
};

ironEND_NAMESPACE