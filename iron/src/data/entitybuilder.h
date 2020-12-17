#pragma once

#include <iron.h>
#include <graphics/spriteinfo.h>
#include <math/vector.h>
#include <item/itemenum.h>

ironBEGIN_NAMESPACE

class Entity;
class Window;

class EntityBuilder
{
public:
    static void BuildInputEntity(Entity* entity);
    static void BuildFurnace(Entity* entity, const Vector2f& position);
    static void BuildInserter(Entity* entity, const Vector2f& position, const Vector2f& direction);
    static void BuildIronOre(Entity* entity, const Vector2f& position);
    static void BuildIronIngot(Entity* entity, const Vector2f& position);
    static void BuildBelt(Entity* entity, const Vector2f& position, const Vector2f& direction);
    static void BuildChest(Entity* entity, const Vector2f& position);
    static void BuildMinion(Entity* entity, const Vector2f& position);
    static void BuildOrePatch(Entity* entity, const Vector2f& position, ResourceType resourceType);
    static void BuildStockPile(Entity* entity, const Vector2f& position);

    static void BuildFromResource(Entity* entity, const Vector2f& position, ResourceType resourceType);
    static void BuildSpriteInfoFromResource(SpriteInfo& spriteInfo, ResourceType resourceType);
};

ironEND_NAMESPACE