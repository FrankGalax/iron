#include <item/inventorysystem.h>
#include <item/inventorycomponent.h>
#include <assert.h>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_1(InventorySystem, InventorySystemTuple, InventoryComponent)

void InventorySystem::Update(float deltaTime)
{
    for (InventorySystemTuple& tuple : m_Tuples)
    {
        std::vector<InventoryItem>& pendingAddItems = tuple.m_InventoryComponent->GetPendingAddItems();
        if (!pendingAddItems.empty())
        {
            std::vector<InventoryItem>& inventoryItems = tuple.m_InventoryComponent->GetItems();
            for (const InventoryItem& pendingAddItem : pendingAddItems)
            {
                bool found = false;
                for (InventoryItem& item : inventoryItems)
                {
                    if (item.m_ResourceType == pendingAddItem.m_ResourceType)
                    {
                        item.m_Quantity++;
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    inventoryItems.push_back(pendingAddItem);
                }
            }

            pendingAddItems.clear();
        }

        std::vector<InventoryItem>& pendingRemoveItems = tuple.m_InventoryComponent->GetPendingRemoveItems();
        if (!pendingRemoveItems.empty())
        {
            std::vector<InventoryItem>& inventoryItems = tuple.m_InventoryComponent->GetItems();
            for (int i = (int)inventoryItems.size() - 1; i >= 0; --i)
            {
                const InventoryItem* foundPendingRemoveItem = nullptr;
                InventoryItem& inventoryItem = inventoryItems[i];

                for (const InventoryItem& pendingRemoveItem : pendingRemoveItems)
                {
                    if (pendingRemoveItem.m_ResourceType == inventoryItem.m_ResourceType)
                    {
                        assert(inventoryItem.m_Quantity >= pendingRemoveItem.m_Quantity);
                        foundPendingRemoveItem = &pendingRemoveItem;
                        break;
                    }
                }

                if (foundPendingRemoveItem != nullptr)
                {
                    inventoryItem.m_Quantity -= foundPendingRemoveItem->m_Quantity;
                    if (inventoryItem.m_Quantity == 0)
                    {
                        InventoryItem temp = inventoryItems[i];
                        inventoryItems[i] = inventoryItems[inventoryItems.size() - 1];
                        inventoryItems[inventoryItems.size() - 1] = temp;
                        inventoryItems.pop_back();
                    }
                }
            }

            pendingRemoveItems.clear();
        }
    }
}

ironEND_NAMESPACE