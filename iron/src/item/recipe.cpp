#include <item/recipe.h>
#include <json.h>

ironBEGIN_NAMESPACE

void Recipe::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    for (InventoryItem& recipeIngredient : m_RecipeIngredients)
    {
        JSON subJSON;
        recipeIngredient.ToJSON(&subJSON);
        j["recipeIngredients"].push_back(subJSON.GetJ());
    }
    j["time"] = m_Time;
}

ironEND_NAMESPACE