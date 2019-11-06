#include <item/craftingsystem.h>
#include <item/craftercomponent.h>
#include <item/inventorycomponent.h>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_2(CraftingSystem, CraftingSystemTuple, CrafterComponent, InventoryComponent)

void CraftingSystem::Update(float deltaTime)
{
    for (CraftingSystemTuple& tuple : m_Tuples)
    {
        CheckPendingAddItem(tuple);
    }
}

void CraftingSystem::CheckPendingAddItem(CraftingSystemTuple& tuple)
{
    const ResourceType pendingAddItem = tuple.m_CrafterComponent->GetPendingAddItem();
    if (pendingAddItem == ResourceType::None)
    {
        return;
    }

    if (tuple.m_CrafterComponent->GetActiveRecipe() != nullptr)
    {
        return;
    }

    const std::vector<Recipe>& recipes = tuple.m_CrafterComponent->GetRecipes();
    for (const Recipe& recipe : recipes)
    {
        for (const RecipeIngredient& ingredient : recipe.m_RecipeIngredients)
        {
            if (ingredient.m_ResourceType == pendingAddItem)
            {
                tuple.m_CrafterComponent->SetPendingAddItemAccepted(true);
                tuple.m_CrafterComponent->SetActiveRecipe(&recipe);
                return;
            }
        }
    }
}

ironEND_NAMESPACE