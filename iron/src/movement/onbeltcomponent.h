#pragma once

#include <iron.h>
#include <ecs/component.h>

ironBEGIN_NAMESPACE

class JSON;
class BeltComponent;

class OnBeltComponent : public Component
{
public:
    OnBeltComponent() {}
    const BeltComponent* GetBelt() const { return m_Belt; }
    void SetBelt(const BeltComponent* belt) { m_Belt = belt; }

    virtual void ToJSON(JSON* j) override;

private:
    const BeltComponent* m_Belt = nullptr;
};

ironEND_NAMESPACE