#include <item/inventorycomponent.h>
#include <json.h>

ironBEGIN_NAMESPACE

void InventoryComponent::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = -308782219;
    for (InventoryItem& item : m_Items)
    {
        JSON subJSON;
        item.ToJSON(&subJSON);
        j["items"].push_back(subJSON.GetJ());
    }
}

void InventoryComponent::FromJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

ironEND_NAMESPACE