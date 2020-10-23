#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <vector>
#include <item/recipe.h>

ironBEGIN_NAMESPACE

class CrafterComponent : public Component
{
public:
	std::vector<Recipe>& GetRecipes() { return m_Recipes; }
    const std::vector<Recipe>& GetRecipes() const { return m_Recipes; }

    void SetActiveRecipe(const Recipe* activeRecipe) { m_ActiveRecipe = activeRecipe; }
    const Recipe* GetActiveRecipe() const { return m_ActiveRecipe; }
    void SetIsCrafting(bool isCrafting) { m_IsCrafting = isCrafting; }
    bool GetIsCrafting() const { return m_IsCrafting; }
    void SetCraftingTime(float craftingTime) { m_CraftingTime = craftingTime; }
    float GetCraftingTime() const { return m_CraftingTime; }

private:
	std::vector<Recipe> m_Recipes;
    const Recipe* m_ActiveRecipe = nullptr;
    bool m_IsCrafting = false;
    float m_CraftingTime = 0.f;
};

ironEND_NAMESPACE