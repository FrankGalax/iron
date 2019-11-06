#include <item/inventorysystem.h>
#include <item/inventorycomponent.h>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_1(InventorySystem, InventorySystemTuple, InventoryComponent)

void InventorySystem::Update(float deltaTime)
{
    for (InventorySystemTuple& tuple : m_Tuples)
    {
        if (tuple.m_InventoryComponent->GetPendingAddItem() != ResourceType::None)
        {
            tuple.m_InventoryComponent->GetItems().push_back(tuple.m_InventoryComponent->GetPendingAddItem());
            tuple.m_InventoryComponent->SetPendingAddItem(ResourceType::None);
        }
    }
}

ironEND_NAMESPACE