#pragma once

#include <iron.h>
#include <item/itemenum.h>

ironBEGIN_NAMESPACE

struct InventoryItem
{
    InventoryItem() : m_ResourceType(ResourceType::None), m_Quantity(0) {}
    InventoryItem(ResourceType resourceType) : m_ResourceType(resourceType), m_Quantity(1) {}
    InventoryItem(ResourceType resourceType, int quantity) : m_ResourceType(resourceType), m_Quantity(quantity) {}

    ResourceType m_ResourceType = ResourceType::None;
    int m_Quantity = 0;
};

ironEND_NAMESPACE