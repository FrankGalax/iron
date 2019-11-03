#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <vector>
#include <item/recipe.h>

ironBEGIN_NAMESPACE

class CrafterComponent : public Component
{
public:
	CrafterComponent() {}

	std::vector<Recipe>& GetRecipes() { return m_Recipes; }

private:
	std::vector<Recipe> m_Recipes;
};

ironEND_NAMESPACE