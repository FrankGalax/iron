#pragma once

#include <iron.h>
#include <ecs/system.h>

ironBEGIN_NAMESPACE

class PathComponent;
class PositionComponent;

class PathSystem : public System
{
    IRON_SYSTEM_DECLARE_2(PathSystemTuple, PathComponent, PositionComponent);

    virtual void Update(float deltaTime) override;
};

ironEND_NAMESPACE