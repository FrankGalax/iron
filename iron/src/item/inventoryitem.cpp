#include <item/inventoryitem.h>
#include <json.h>

ironBEGIN_NAMESPACE

void InventoryItem::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = 1586531887;
    j["resourceType"] = (int)m_ResourceType;
    j["quantity"] = m_Quantity;
    j["isOutput"] = m_IsOutput;
}

void InventoryItem::FromJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

ironEND_NAMESPACE