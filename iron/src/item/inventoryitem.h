#pragma once

#include <iron.h>

#pragma region usercode
#include <item/itemenum.h>
#pragma endregion

ironBEGIN_NAMESPACE

class JSON;

class InventoryItem
{
public:
    InventoryItem() {}
    InventoryItem(ResourceType resourceType, int quantity, bool isOutput) : m_ResourceType(resourceType), m_Quantity(quantity), m_IsOutput(isOutput) {}

    ResourceType GetResourceType() const { return m_ResourceType; }
    void SetResourceType(ResourceType resourceType) { m_ResourceType = resourceType; }
    int GetQuantity() const { return m_Quantity; }
    void SetQuantity(int quantity) { m_Quantity = quantity; }
    bool GetIsOutput() const { return m_IsOutput; }
    void SetIsOutput(bool isOutput) { m_IsOutput = isOutput; }

    void ToJSON(JSON* j);
    void FromJSON(JSON* j);
    void FromJSONResolve(JSON* j);

private:
    ResourceType m_ResourceType = ResourceType::None;
    int m_Quantity = 0;
    bool m_IsOutput = false;

#pragma region usercodeclass
public:
    InventoryItem(ResourceType resourceType) : m_ResourceType(resourceType), m_Quantity(1), m_IsOutput(false) {}
    InventoryItem(ResourceType resourceType, int quantity) : m_ResourceType(resourceType), m_Quantity(quantity), m_IsOutput(false) {}
#pragma endregion
};

ironEND_NAMESPACE