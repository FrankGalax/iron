#include <data/entitybuilder.h>
#include <ecs/entity.h>
#include <graphics/spritecomponent.h>
#include <movement/beltcomponent.h>
#include <item/craftercomponent.h>
#include <item/inventorycomponent.h>
#include <item/resourcecomponent.h>
#include <movement/insertercomponent.h>
#include <movement/positioncomponent.h>
#include <assert.h>

ironBEGIN_NAMESPACE

void EntityBuilder::BuildFurnace(Entity* entity, const Vector2f& position)
{
    entity->SetName("furnace");
    entity->AddComponent(new SpriteComponent(12, 2, 2.f, 2.f));
    entity->AddComponent(new PositionComponent(position, 2, 2));
    entity->AddComponent(new InserterComponent(InserterComponent::InserterType::Insertable));
    CrafterComponent* furnaceCrafterComponent = new CrafterComponent();
    std::vector<Recipe>& recipes = furnaceCrafterComponent->GetRecipes();
    {
        Recipe recipe;
        recipe.m_Time = 2.f;
        recipe.m_Product.m_Quantity = 1;
        recipe.m_Product.m_ResourceType = ResourceType::IronIngot;
        InventoryItem recipeIngredient(ResourceType::IronOre, 1);
        recipe.m_RecipeIngredients.push_back(recipeIngredient);
        recipes.push_back(recipe);
    }
    entity->AddComponent(furnaceCrafterComponent);
    entity->AddComponent(new InventoryComponent());
}

void EntityBuilder::BuildInserter(Entity* entity, const Vector2f& position)
{
    entity->SetName("inserter");
    entity->AddComponent(new SpriteComponent(18, 11, 1.f, 1.f));
    entity->AddComponent(new PositionComponent(position));
    entity->AddComponent(new InserterComponent(InserterComponent::InserterType::Inserter, Vector2f(0.f, -1.f), Vector2f(0.f, 1.f)));
}

void EntityBuilder::BuildIronOre(Entity* entity, const Vector2f& position)
{
    entity->SetName("ironOre");
    entity->AddComponent(new SpriteComponent(0, 58, 1.f, 1.f));
    entity->AddComponent(new PositionComponent(position));
    entity->AddComponent(new InserterComponent(InserterComponent::InserterType::Insertable));
    entity->AddComponent(new ResourceComponent(ResourceType::IronOre));
}

void EntityBuilder::BuildIronIngot(Entity* entity, const Vector2f& position)
{
    entity->SetName("ironIngot");
    entity->AddComponent(new SpriteComponent(4, 15, 1.f, 1.f));
    entity->AddComponent(new PositionComponent(position));
}

void EntityBuilder::BuildBelt(Entity* entity, const Vector2f& position)
{
    entity->SetName("belt");
    entity->AddComponent(new SpriteComponent(16, 12, 1.f, 1.f));
    entity->AddComponent(new PositionComponent(position));
    entity->AddComponent(new BeltComponent());
    entity->AddComponent(new InserterComponent(InserterComponent::InserterType::Insertable));
}

void EntityBuilder::BuildFromResource(Entity* entity, const Vector2f& position, ResourceType resourceType)
{
    switch (resourceType)
    {
    case ResourceType::IronIngot:
        BuildIronIngot(entity, position);
        return;
    }

    assert(false);
}

ironEND_NAMESPACE