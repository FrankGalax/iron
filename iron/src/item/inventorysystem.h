#pragma once

#include <iron.h>
#include <ecs/system.h>

ironBEGIN_NAMESPACE

class InventoryComponent;

class InventorySystem : public System
{
    IRON_SYSTEM_DECLARE_1(InventorySystemTuple, InventoryComponent);

    virtual void Update(float deltaTime) override;
};

ironEND_NAMESPACE