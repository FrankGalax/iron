#include <item/craftingsystem.h>
#include <item/craftercomponent.h>
#include <item/inventorycomponent.h>
#include <utils.h>
#include <iostream>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_2(CraftingSystem, CraftingSystemTuple, CrafterComponent, InventoryComponent)

void CraftingSystem::Update(float deltaTime)
{
    for (CraftingSystemTuple& tuple : m_Tuples)
    {
        CheckPendingRecipe(tuple);
        CheckActiveRecipe(tuple);
        CheckCrafting(tuple, deltaTime);
    }
}

void CraftingSystem::CheckPendingRecipe(CraftingSystemTuple& tuple)
{
    const std::vector<InventoryItem>& inventoryItems = tuple.m_InventoryComponent->GetItems();
    if (tuple.m_CrafterComponent->GetActiveRecipe() != nullptr)
    {
        return;
    }

    const std::vector<Recipe>& recipes = tuple.m_CrafterComponent->GetRecipes();
    for (const Recipe& recipe : recipes)
    {
        for (const InventoryItem& inventoryItem : inventoryItems)
        {
            for (const InventoryItem& ingredient : recipe.GetRecipeIngredients())
            {
                if (ingredient.GetResourceType() == inventoryItem.GetResourceType() && ingredient.GetQuantity() <= inventoryItem.GetQuantity())
                {
                    tuple.m_CrafterComponent->SetActiveRecipe(&recipe);
                    return;
                }
            }
        }
    }
}

void CraftingSystem::CheckActiveRecipe(CraftingSystemTuple& tuple)
{
    if (tuple.m_CrafterComponent->GetIsCrafting())
    {
        return;
    }

    const Recipe* recipe = tuple.m_CrafterComponent->GetActiveRecipe();
    if (recipe == nullptr)
    {
        return;
    }

    bool inventoryComplete = true;
    const std::vector<InventoryItem>& inventoryItems = tuple.m_InventoryComponent->GetItems();
    for (const InventoryItem& ingredient : recipe->GetRecipeIngredients())
    {
        bool itemFound = false;
        for (const InventoryItem& inventoryItem : inventoryItems)
        {
            if (inventoryItem.GetResourceType() == ingredient.GetResourceType() &&
                inventoryItem.GetQuantity() >= ingredient.GetQuantity())
            {
                itemFound = true;
                break;
            }
        }

        if (!itemFound)
        {
            inventoryComplete = false;
            break;
        }
    }

    if (!inventoryComplete)
    {
        return;
    }

    std::vector<InventoryItem>& pendingRemoveItems = tuple.m_InventoryComponent->GetPendingRemoveItems();
    for (const InventoryItem& ingredient : recipe->GetRecipeIngredients())
    {
        pendingRemoveItems.push_back(ingredient);
    }
    
    tuple.m_CrafterComponent->SetIsCrafting(true);
}

void CraftingSystem::CheckCrafting(CraftingSystemTuple& tuple, float deltaTime)
{
    if (!tuple.m_CrafterComponent->GetIsCrafting() || tuple.m_CrafterComponent->GetActiveRecipe() == nullptr)
    {
        return;
    }

    const float craftingTime = tuple.m_CrafterComponent->GetCraftingTime() + deltaTime;
    tuple.m_CrafterComponent->SetCraftingTime(craftingTime);

    const Recipe* activeRecipe = tuple.m_CrafterComponent->GetActiveRecipe();
    if (craftingTime >= activeRecipe->GetTime())
    {
        InventoryItem product = activeRecipe->GetProduct();
        product.SetIsOutput(true);
        tuple.m_InventoryComponent->GetPendingAddItems().push_back(product);
        tuple.m_CrafterComponent->SetCraftingTime(0.f);
        tuple.m_CrafterComponent->SetIsCrafting(false);
        tuple.m_CrafterComponent->SetActiveRecipe(nullptr);

        std::cout << "Crafted " << Utils::GetRessourceName(product.GetResourceType()) << " in " << tuple.m_Entity->GetName().c_str() << std::endl;
    }
}

ironEND_NAMESPACE