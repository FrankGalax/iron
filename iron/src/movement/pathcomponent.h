#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <math/vector.h>

ironBEGIN_NAMESPACE

class JSON;

class PathComponent : public Component
{
public:
    PathComponent() {}
    Vector2f& GetTarget() { return m_Target; }
    const Vector2f& GetTarget() const { return m_Target; }
    void SetTarget(const Vector2f& target) { m_Target = target; }

    virtual void ToJSON(JSON* j) override;
    virtual void FromJSON(JSON* j) override;
    virtual void FromJSONResolve(JSON* j) override;

private:
    Vector2f m_Target;
};

ironEND_NAMESPACE