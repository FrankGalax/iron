#pragma once

#include <iron.h>
#include <item/itemenum.h>

ironBEGIN_NAMESPACE

struct InventoryItem
{
    InventoryItem() {}
    InventoryItem(ResourceType resourceType) : m_ResourceType(resourceType), m_Quantity(1) {}
    InventoryItem(ResourceType resourceType, int quantity) : m_ResourceType(resourceType), m_Quantity(quantity) {}

    ResourceType m_ResourceType = ResourceType::None;
    int m_Quantity = 0;
    bool m_IsOutput = false;
};

ironEND_NAMESPACE