#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <vector>

#pragma region usercode
#include <item/itemenum.h>
#include <item/inventoryitem.h>
#pragma endregion

ironBEGIN_NAMESPACE

class JSON;

class InventoryComponent : public Component
{
public:
    InventoryComponent() {}
    std::vector<InventoryItem>& GetItems() { return m_Items; }
    const std::vector<InventoryItem>& GetItems() const { return m_Items; }

    virtual void ToJSON(JSON* j) override;
    virtual void FromJSON(JSON* j) override;
    virtual void FromJSONResolve(JSON* j) override;

private:
    std::vector<InventoryItem> m_Items;

#pragma region usercodeclass
public:
    std::vector<InventoryItem>& GetPendingAddItems() { return m_PendingAddItems; }
    std::vector<InventoryItem>& GetPendingRemoveItems() { return m_PendingRemoveItems; }
    bool GetIsDirtyForUI() const { return m_IsDirtyForUI; }
    void SetIsDirtyForUI(bool isDirtyForUI) { m_IsDirtyForUI = isDirtyForUI; }

private:
    std::vector<InventoryItem> m_PendingAddItems;
    std::vector<InventoryItem> m_PendingRemoveItems;
    bool m_IsDirtyForUI = false;
#pragma endregion
};

ironEND_NAMESPACE