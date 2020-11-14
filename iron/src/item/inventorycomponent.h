#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <vector>
#include <item/itemenum.h>
#include <item/inventoryitem.h>

ironBEGIN_NAMESPACE

class InventoryComponent : public Component
{
public:
    std::vector<InventoryItem>& GetItems() { return m_Items; }
    const std::vector<InventoryItem>& GetItems() const { return m_Items; }
    std::vector<InventoryItem>& GetPendingAddItems() { return m_PendingAddItems; }
    std::vector<InventoryItem>& GetPendingRemoveItems() { return m_PendingRemoveItems; }
    bool GetIsDirtyForUI() const { return m_IsDirtyForUI; }
    void SetIsDirtyForUI(bool isDirtyForUI) { m_IsDirtyForUI = isDirtyForUI; }

private:
    std::vector<InventoryItem> m_Items;
    std::vector<InventoryItem> m_PendingAddItems;
    std::vector<InventoryItem> m_PendingRemoveItems;
    bool m_IsDirtyForUI = false;
};
ironEND_NAMESPACE