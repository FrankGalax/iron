#include <item/inventoryitem.h>
#include <json.h>

ironBEGIN_NAMESPACE

void InventoryItem::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["quantity"] = m_Quantity;
    j["isOutput"] = m_IsOutput;
}

ironEND_NAMESPACE