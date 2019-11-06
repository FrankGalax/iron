#pragma once

#include <iron.h>
#include <ecs/system.h>

ironBEGIN_NAMESPACE

class InserterComponent;
class PositionComponent;
class CrafterComponent;
class ResourceComponent;
class InventoryComponent;

class InserterSystem : public System
{
    IRON_SYSTEM_DECLARE_5(InserterSystemTuple, InserterComponent, PositionComponent, CrafterComponent, ResourceComponent, InventoryComponent)

    virtual void Update(float deltaTime) override;
};

ironEND_NAMESPACE