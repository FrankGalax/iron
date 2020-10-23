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
    void CheckPendingRecipe(CraftingSystemTuple& tuple);
    void CheckActiveRecipe(CraftingSystemTuple& tuple);
    void CheckCrafting(CraftingSystemTuple& tuple, float deltaTime);
};

ironEND_NAMESPACE