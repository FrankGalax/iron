#pragma once

#include <iron.h>
#include <ecs/system.h>

ironBEGIN_NAMESPACE

class InserterComponent;
class PositionComponent;

class InserterSystem : public System
{
    IRON_SYSTEM_DECLARE_2(InserterSystemTuple, InserterComponent, PositionComponent)

    virtual void Update(float deltaTime) override;
};

ironEND_NAMESPACE