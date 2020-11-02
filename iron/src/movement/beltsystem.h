#pragma once

#include <iron.h>
#include <ecs/system.h>

ironBEGIN_NAMESPACE

class OnBeltComponent;
class PositionComponent;

class BeltSystem : public System
{
    IRON_SYSTEM_DECLARE_2(BeltSystemTuple, OnBeltComponent, PositionComponent);

    virtual void Update(float deltaTime) override;
};

ironEND_NAMESPACE