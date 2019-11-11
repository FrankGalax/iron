#pragma once

#include <iron.h>
#include <vector>
#include <item/itemenum.h>
#include <item/inventoryitem.h>

ironBEGIN_NAMESPACE

struct Recipe
{
	InventoryItem m_Product;
	std::vector<InventoryItem> m_RecipeIngredients;
	float m_Time = 0.f;
};

ironEND_NAMESPACE