#pragma once

#include <iron.h>
#include <ecs/system.h>

ironBEGIN_NAMESPACE

class CrafterComponent;
class InventoryComponent;

class CraftingSystem : public System
{
    IRON_SYSTEM_DECLARE_2(CraftingSystemTuple, CrafterComponent, InventoryComponent);

    virtual void Update(float deltaTime) override;

private:
    void CheckPendingAddItem(CraftingSystemTuple& tuple);
};

ironEND_NAMESPACE