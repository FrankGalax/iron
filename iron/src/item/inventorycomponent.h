#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <vector>
#include <item/itemenum.h>

ironBEGIN_NAMESPACE

class InventoryComponent : public Component
{
public:
    std::vector<ResourceType>& GetItems() { return m_Items; }
    void SetPendingAddItem(ResourceType pendingAddItem) { m_PendingAddItem = pendingAddItem; }
    ResourceType GetPendingAddItem() const { return m_PendingAddItem; }

private:
    std::vector<ResourceType> m_Items;
    ResourceType m_PendingAddItem;
};
ironEND_NAMESPACE