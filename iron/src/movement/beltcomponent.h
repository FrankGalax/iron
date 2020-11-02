#pragma once

#include <iron.h>
#include <ecs/component.h>

ironBEGIN_NAMESPACE

class BeltComponent : public Component
{
public:
    BeltComponent* GetNextBelt() const { return m_NextBelt; }
    void SetNextBelt(BeltComponent* nextBelt) { m_NextBelt = nextBelt; }
    float GetSpeed() const { return m_Speed; }

private:
    BeltComponent* m_NextBelt;
    float m_Speed = 1.f;
};

ironEND_NAMESPACE