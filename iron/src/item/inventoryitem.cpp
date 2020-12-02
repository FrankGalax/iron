#include <item/inventoryitem.h>
#include <json.h>

ironBEGIN_NAMESPACE

void InventoryItem::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
}

ironEND_NAMESPACE