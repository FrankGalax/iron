#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <vector>

#pragma region usercode
#include <item/recipe.h>
#pragma endregion

ironBEGIN_NAMESPACE

class JSON;

class CrafterComponent : public Component
{
public:
    CrafterComponent() {}
    std::vector<Recipe>& GetRecipes() { return m_Recipes; }
    const std::vector<Recipe>& GetRecipes() const { return m_Recipes; }
    const Recipe* GetActiveRecipe() const { return m_ActiveRecipe; }
    void SetActiveRecipe(const Recipe* activeRecipe) { m_ActiveRecipe = activeRecipe; }
    bool GetIsCrafting() const { return m_IsCrafting; }
    void SetIsCrafting(bool isCrafting) { m_IsCrafting = isCrafting; }
    float GetCraftingTime() const { return m_CraftingTime; }
    void SetCraftingTime(float craftingTime) { m_CraftingTime = craftingTime; }

    virtual void ToJSON(JSON* j) override;

private:
    std::vector<Recipe> m_Recipes;
    const Recipe* m_ActiveRecipe = nullptr;
    bool m_IsCrafting = false;
    float m_CraftingTime = 0.f;
};

ironEND_NAMESPACE