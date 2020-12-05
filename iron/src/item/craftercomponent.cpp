#include <item/craftercomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void CrafterComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = 1338292626;
    for (Recipe& recipe : m_Recipes)
    {
        JSON subJSON;
        recipe.ToJSON(&subJSON);
        j["recipes"].push_back(subJSON.GetJ());
    }
}

void CrafterComponent::FromJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    for (nlohmann::json& recipeJ : j["recipes"])
    {
        Recipe recipe;
        JSON recipeJSON(recipeJ);
        recipe.FromJSON(&recipeJSON);
        m_Recipes.push_back(recipe);
    }
}

ironEND_NAMESPACE