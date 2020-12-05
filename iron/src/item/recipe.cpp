#include <item/recipe.h>
#include <json.h>

ironBEGIN_NAMESPACE

void Recipe::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = 1590435104;
    JSON productJson;
    m_Product.ToJSON(&productJson);
    j["product"] = productJson.GetJ();
    for (InventoryItem& recipeIngredient : m_RecipeIngredients)
    {
        JSON subJSON;
        recipeIngredient.ToJSON(&subJSON);
        j["recipeIngredients"].push_back(subJSON.GetJ());
    }
    j["time"] = m_Time;
}

void Recipe::FromJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    JSON productJSON(j["product"]);
    m_Product.FromJSON(&productJSON);
    for (nlohmann::json& recipeIngredientJ : j["recipeIngredients"])
    {
        InventoryItem recipeIngredient;
        JSON recipeIngredientJSON(recipeIngredientJ);
        recipeIngredient.FromJSON(&recipeIngredientJSON);
        m_RecipeIngredients.push_back(recipeIngredient);
    }
    m_Time = j["time"];
}

ironEND_NAMESPACE