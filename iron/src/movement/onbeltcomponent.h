#pragma once

#include <iron.h>
#include <ecs/component.h>

ironBEGIN_NAMESPACE

class BeltComponent;

class OnBeltComponent : public Component
{
public:
    const BeltComponent* GetBelt() const { return m_Belt; }
    void SetBelt(const BeltComponent* belt) { m_Belt = belt; }

private:
    const BeltComponent* m_Belt;
};

ironEND_NAMESPACE