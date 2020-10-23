#pragma once

#include <iron.h>
#include <ecs/system.h>

ironBEGIN_NAMESPACE

class BeltComponent;

class BeltSystem : public System
{
    IRON_SYSTEM_DECLARE_1(BeltSystemTuple, BeltComponent);

    virtual void Update(float deltaTime) override;
};

ironEND_NAMESPACE