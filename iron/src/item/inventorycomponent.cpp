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
    for (nlohmann::json& itemJ : j["items"])
    {
        InventoryItem item;
        JSON itemJSON(itemJ);
        item.FromJSON(&itemJSON);
        m_Items.push_back(item);
    }
}

void InventoryComponent::FromJSONResolve(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    for (int i = 0; i < m_Items.size(); ++i)
    {
        JSON itemJSON(j["items"][i]);
        m_Items[i].FromJSONResolve(&itemJSON);
    }
}

ironEND_NAMESPACE