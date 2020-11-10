#pragma once

#include <iron.h>
#include <math/vector.h>
#include <item/itemenum.h>

ironBEGIN_NAMESPACE

class Entity;

class EntityBuilder
{
public:
    static void BuildFurnace(Entity* entity, const Vector2f& position);
    static void BuildInserter(Entity* entity, const Vector2f& position);
    static void BuildIronOre(Entity* entity, const Vector2f& position);
    static void BuildIronIngot(Entity* entity, const Vector2f& position);
    static void BuildBelt(Entity* entity, const Vector2f& position, const Vector2f& direction);
    static void BuildChest(Entity* entity, const Vector2f& position);

    static void BuildFromResource(Entity* entity, const Vector2f& position, ResourceType resourceType);
};

ironEND_NAMESPACE