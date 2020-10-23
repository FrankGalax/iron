#pragma once

#include <iron.h>
#include <ecs/system.h>

ironBEGIN_NAMESPACE

class InserterComponent;
class PositionComponent;
class ResourceComponent;
class InventoryComponent;

class InserterSystem : public System
{
    IRON_SYSTEM_DECLARE_4(InserterSystemTuple, InserterComponent, PositionComponent, ResourceComponent, InventoryComponent)

    virtual void Update(float deltaTime) override;
};

ironEND_NAMESPACE