#pragma once

#include <iron.h>
#include <vector>
#include <item/itemenum.h>

ironBEGIN_NAMESPACE

struct RecipeIngredient
{
	ResourceType m_ResourceType = ResourceType::None;
	int m_Quantity = 0;
};

struct Recipe
{
	RecipeIngredient m_Product;
	std::vector<RecipeIngredient> m_RecipeIngredients;
	float m_Time = 0.f;
};

ironEND_NAMESPACE