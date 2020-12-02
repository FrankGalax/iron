#include <item/craftercomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void CrafterComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    for (Recipe& recipe : m_Recipes)
    {
        JSON subJSON;
        recipe.ToJSON(&subJSON);
        j["recipes"].push_back(subJSON.GetJ());
    }
    j["isCrafting"] = m_IsCrafting;
    j["craftingTime"] = m_CraftingTime;
}

ironEND_NAMESPACE