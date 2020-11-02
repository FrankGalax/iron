#pragma once

#include <iron.h>
#include <ecs/system.h>

ironBEGIN_NAMESPACE

class InserterComponent;
class PositionComponent;
class ResourceComponent;
class InventoryComponent;
class BeltComponent;

class InserterSystem : public System
{
    IRON_SYSTEM_DECLARE_5(InserterSystemTuple, InserterComponent, PositionComponent, ResourceComponent, InventoryComponent, BeltComponent)

    virtual void Update(float deltaTime) override;
};

ironEND_NAMESPACE