#pragma once

#include <iron.h>
#include <ecs/system.h>

ironBEGIN_NAMESPACE

class PositionNotifyComponent;
class PositionComponent;

class PositionNotifySystem : public System
{
    IRON_SYSTEM_DECLARE_2(PositionNotifySystemTuple, PositionNotifyComponent, PositionComponent)

    virtual void Update(float deltaTime) override;
};

ironEND_NAMESPACE