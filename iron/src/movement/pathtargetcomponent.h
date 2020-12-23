#pragma once

#include <iron.h>
#include <ecs/component.h>

ironBEGIN_NAMESPACE

class JSON;

class PathTargetComponent : public Component
{
public:
    PathTargetComponent() {}

    virtual void ToJSON(JSON* j) override;
    virtual void FromJSON(JSON* j) override;
    virtual void FromJSONResolve(JSON* j) override;

private:
};

ironEND_NAMESPACE