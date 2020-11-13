#include <data/entitybuilder.h>
#include <ecs/entity.h>
#include <graphics/spritecomponent.h>
#include <graphics/animationcomponent.h>
#include <movement/beltcomponent.h>
#include <input/inputcomponent.h>
#include <item/craftercomponent.h>
#include <item/inventorycomponent.h>
#include <item/resourcecomponent.h>
#include <movement/insertercomponent.h>
#include <movement/positioncomponent.h>
#include <assert.h>

ironBEGIN_NAMESPACE

void EntityBuilder::BuildInputEntity(Entity* entity, const Window* window)
{
    entity->SetName("input");
    entity->AddComponent(new InputComponent(window));
}

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
    entity->AddComponent(new InserterComponent(InserterComponent::InserterType::Inserter, Vector2f(0.f, -0.02f), Vector2f(0.f, 1.f)));
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
    entity->AddComponent(new InserterComponent(InserterComponent::InserterType::Insertable));
    entity->AddComponent(new ResourceComponent(ResourceType::IronIngot));
}

void EntityBuilder::BuildBelt(Entity* entity, const Vector2f& position, const Vector2f& direction)
{
    entity->SetName("belt");
    
    if (ironNullWithEpsilon(direction.GetY()))
    {
        entity->AddComponent(new SpriteComponent(16, 12, 1.f, 1.f));
    }
    else if (ironNullWithEpsilon(direction.GetX()))
    {
        entity->AddComponent(new SpriteComponent(0, 8, 1.f, 1.f));
    }
    entity->AddComponent(new PositionComponent(position));
    BeltComponent* beltComponent = new BeltComponent();
    beltComponent->SetDirection(direction);
    entity->AddComponent(beltComponent);
    InserterComponent* inserterComponent = new InserterComponent(InserterComponent::InserterType::Insertable);
    inserterComponent->SetIsInsertableOutOnly(true);
    entity->AddComponent(inserterComponent);
    
    AnimationComponent* animationComponent = new AnimationComponent();
    std::vector<AnimationSprite>& animationSprites = animationComponent->GetAnimationSprites();
    animationSprites.resize(4);

    if (direction.Equals(Vector2f::Right))
    {
        animationSprites[0].SetSpriteSheetXY(16, 12);
        animationSprites[1].SetSpriteSheetXY(24, 0);
        animationSprites[2].SetSpriteSheetXY(24, 1);
        animationSprites[3].SetSpriteSheetXY(24, 2);
    }
    else if (direction.Equals(Vector2f::Down))
    {
        animationSprites[0].SetSpriteSheetXY(0, 8);
        animationSprites[1].SetSpriteSheetXY(24, 3);
        animationSprites[2].SetSpriteSheetXY(24, 4);
        animationSprites[3].SetSpriteSheetXY(24, 5);
    }
    else if (direction.Equals(Vector2f::Left))
    {
        animationSprites[0].SetSpriteSheetXY(16, 12);
        animationSprites[1].SetSpriteSheetXY(24, 2);
        animationSprites[2].SetSpriteSheetXY(24, 1);
        animationSprites[3].SetSpriteSheetXY(24, 0);
    }
    else if (direction.Equals(Vector2f::Up))
    {
        animationSprites[0].SetSpriteSheetXY(0, 8);
        animationSprites[1].SetSpriteSheetXY(24, 5);
        animationSprites[2].SetSpriteSheetXY(24, 4);
        animationSprites[3].SetSpriteSheetXY(24, 3);
    }

    const float time = 1.f / (beltComponent->GetSpeed() * GRID_SIZE);
    animationComponent->SetTime(time);
    animationComponent->SetTimer(time);
    entity->AddComponent(animationComponent);
}

void EntityBuilder::BuildChest(Entity* entity, const Vector2f& position)
{
    entity->SetName("chest");
    entity->AddComponent(new SpriteComponent(21, 5, 1.f, 1.f));
    entity->AddComponent(new PositionComponent(position));
    entity->AddComponent(new InserterComponent(InserterComponent::InserterType::Insertable));
    entity->AddComponent(new InventoryComponent());
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