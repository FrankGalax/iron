#pragma once

#include <iron.h>
#include <vector>

#pragma region usercode
#include <item/inventoryitem.h>
#pragma endregion

ironBEGIN_NAMESPACE

class JSON;

class Recipe
{
public:
    Recipe() {}
    Recipe(const InventoryItem& product, float time) : m_Product(product), m_Time(time) {}

    const InventoryItem& GetProduct() const { return m_Product; }
    void SetProduct(const InventoryItem& product) { m_Product = product; }
    std::vector<InventoryItem>& GetRecipeIngredients() { return m_RecipeIngredients; }
    const std::vector<InventoryItem>& GetRecipeIngredients() const { return m_RecipeIngredients; }
    float GetTime() const { return m_Time; }
    void SetTime(float time) { m_Time = time; }

    void ToJSON(JSON* j);

private:
    InventoryItem m_Product;
    std::vector<InventoryItem> m_RecipeIngredients;
    float m_Time = 0.f;
};

ironEND_NAMESPACE