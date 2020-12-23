#include <data/entitybuilder.h>
#include <ecs/entity.h>
#include <graphics/spritecomponent.h>
#include <graphics/animationcomponent.h>
#include <movement/beltcomponent.h>
#include <input/inputcomponent.h>
#include <item/craftercomponent.h>
#include <item/inventorycomponent.h>
#include <item/recipe.h>
#include <item/resourcecomponent.h>
#include <movement/insertercomponent.h>
#include <movement/pathcomponent.h>
#include <movement/pathtargetcomponent.h>
#include <movement/positioncomponent.h>
#include <ui/uicomponent.h>
#include <assert.h>

ironBEGIN_NAMESPACE

void EntityBuilder::BuildInputEntity(Entity* entity)
{
    entity->SetName("input");
    entity->AddComponent(new InputComponent());
    entity->AddComponent(new UIComponent());
}

void EntityBuilder::BuildFurnace(Entity* entity, const Vector2f& position)
{
    entity->SetName("furnace");
    entity->AddComponent(new SpriteComponent(12, 2, 2.f, 2.f, 0.f, 0));
    entity->AddComponent(new PositionComponent(position, Vector2f(2.f, 2.f)));
    entity->AddComponent(new InserterComponent(InserterType::Insertable));
    CrafterComponent* furnaceCrafterComponent = new CrafterComponent();
    std::vector<Recipe>& recipes = furnaceCrafterComponent->GetRecipes();
    {
        InventoryItem product(ResourceType::IronIngot);
        Recipe recipe(product, 2.f);
        InventoryItem recipeIngredient(ResourceType::IronOre, 1);
        recipe.GetRecipeIngredients().push_back(recipeIngredient);
        recipes.push_back(recipe);
    }
    entity->AddComponent(furnaceCrafterComponent);
    entity->AddComponent(new InventoryComponent());
}

void EntityBuilder::BuildInserter(Entity* entity, const Vector2f& position, const Vector2f& direction)
{
    entity->SetName("inserter");
    if (direction.Equals(Vector2f::Down))
    {
        entity->AddComponent(new SpriteComponent(18, 11, 1.f, 1.f, 0.f, 0));
        entity->AddComponent(new InserterComponent(InserterType::Inserter, Vector2f(0.5f, -0.02f), Vector2f(0.5f, 1.5f)));
    }
    else if (direction.Equals(Vector2f::Right))
    {
        entity->AddComponent(new SpriteComponent(18, 11, 1.f, 1.f, 270.f, 0));
        entity->AddComponent(new InserterComponent(InserterType::Inserter, Vector2f(-0.02f, 0.5f), Vector2f(1.5f, 0.5f)));
    }
    else if (direction.Equals(Vector2f::Up))
    {
        entity->AddComponent(new SpriteComponent(18, 11, 1.f, 1.f, 180.f, 0));
        entity->AddComponent(new InserterComponent(InserterType::Inserter, Vector2f(0.5f, 1.02f), Vector2f(0.5f, -0.5f)));
    }
    else if (direction.Equals(Vector2f::Left))
    {
        entity->AddComponent(new SpriteComponent(18, 11, 1.f, 1.f, 90.f, 0));
        entity->AddComponent(new InserterComponent(InserterType::Inserter, Vector2f(1.02f, 0.5f), Vector2f(-0.5f, 0.5f)));
    }

    entity->AddComponent(new PositionComponent(position));
}

void EntityBuilder::BuildIronOre(Entity* entity, const Vector2f& position)
{
    entity->SetName("ironOre");
    SpriteInfo spriteInfo;
    BuildSpriteInfoFromResource(spriteInfo, ResourceType::IronOre);
    entity->AddComponent(new SpriteComponent(spriteInfo));
    entity->AddComponent(new PositionComponent(position));
    entity->AddComponent(new InserterComponent(InserterType::Insertable));
    entity->AddComponent(new ResourceComponent(ResourceType::IronOre));
}

void EntityBuilder::BuildIronIngot(Entity* entity, const Vector2f& position)
{
    entity->SetName("ironIngot");
    SpriteInfo spriteInfo;
    BuildSpriteInfoFromResource(spriteInfo, ResourceType::IronIngot);
    entity->AddComponent(new SpriteComponent(spriteInfo));
    entity->AddComponent(new PositionComponent(position));
    entity->AddComponent(new InserterComponent(InserterType::Insertable));
    entity->AddComponent(new ResourceComponent(ResourceType::IronIngot));
}

void EntityBuilder::BuildBelt(Entity* entity, const Vector2f& position, const Vector2f& direction)
{
    entity->SetName("belt");
    
    if (ironNullWithEpsilon(direction.GetY()))
    {
        entity->AddComponent(new SpriteComponent(16, 12, 1.f, 1.f, 0.f, 0));
    }
    else if (ironNullWithEpsilon(direction.GetX()))
    {
        entity->AddComponent(new SpriteComponent(0, 8, 1.f, 1.f, 0.f, 0));
    }
    entity->AddComponent(new PositionComponent(position));
    BeltComponent* beltComponent = new BeltComponent();
    beltComponent->SetDirection(direction);
    entity->AddComponent(beltComponent);
    InserterComponent* inserterComponent = new InserterComponent(InserterType::Insertable);
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
    entity->AddComponent(new SpriteComponent(21, 5, 1.f, 1.f, 0.f, 0));
    entity->AddComponent(new PositionComponent(position));
    entity->AddComponent(new InserterComponent(InserterType::Insertable));
    entity->AddComponent(new InventoryComponent());
}

void EntityBuilder::BuildMinion(Entity* entity, const Vector2f& position)
{
    entity->SetName("minion");
    entity->AddComponent(new SpriteComponent(20, 9, 1.f, 1.f, 0.f, 0));
    entity->AddComponent(new PositionComponent(position));
    entity->AddComponent(new InventoryComponent());
    entity->AddComponent(new PathComponent());
}

void EntityBuilder::BuildOrePatch(Entity* entity, const Vector2f& position, ResourceType resourceType)
{
    entity->SetName("orePatch");
    entity->AddComponent(new SpriteComponent(1, 2, 2.f, 2.f, 0.f, 0));
    entity->AddComponent(new PositionComponent(position, Vector2f(2.f, 2.f)));
    entity->AddComponent(new ResourceComponent(resourceType));
}

void EntityBuilder::BuildStockPile(Entity* entity, const Vector2f& position)
{
    entity->SetName("stockPile");
    entity->AddComponent(new SpriteComponent(5, 1, 1.f, 1.f, 0.f, 0));
    entity->AddComponent(new PositionComponent(position));
    InserterComponent* inserterComponent = new InserterComponent(InserterType::Insertable);
    inserterComponent->SetIsInsertableOutOnly(true);
    entity->AddComponent(inserterComponent);
    entity->AddComponent(new InventoryComponent());
    entity->AddComponent(new PathTargetComponent());
}

void EntityBuilder::BuildFromResource(Entity* entity, const Vector2f& position, ResourceType resourceType)
{
    switch (resourceType)
    {
    case ResourceType::IronOre:
        BuildIronOre(entity, position);
        return;
    case ResourceType::IronIngot:
        BuildIronIngot(entity, position);
        return;
    }

    assert(false);
}

void EntityBuilder::BuildSpriteInfoFromResource(SpriteInfo& spriteInfo, ResourceType resourceType)
{
    switch (resourceType)
    {
    case ResourceType::IronOre:
        spriteInfo.m_SpriteSheetX = 0;
        spriteInfo.m_SpriteSheetY = 58;
        spriteInfo.m_Priority = 5;
        return;
    case ResourceType::IronIngot:
        spriteInfo.m_SpriteSheetX = 4;
        spriteInfo.m_SpriteSheetY = 15;
        spriteInfo.m_Priority = 5;
        return;
    }

    assert(false);
}

ironEND_NAMESPACE