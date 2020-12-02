#pragma once

#include <iron.h>
#include <ecs/component.h>

ironBEGIN_NAMESPACE

class JSON;
class BeltComponent;

class OnBeltComponent : public Component
{
public:
    const BeltComponent* GetBelt() const { return m_Belt; }
    void SetBelt(const BeltComponent* belt) { m_Belt = belt; }

    void ToJSON(JSON* j);

private:
    const BeltComponent* m_Belt = nullptr;
};

ironEND_NAMESPACE