#include <item/craftercomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void CrafterComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = 1448254106;
    for (Recipe& recipe : m_Recipes)
    {
        JSON subJSON;
        recipe.ToJSON(&subJSON);
        j["recipes"].push_back(subJSON.GetJ());
    }
}

ironEND_NAMESPACE