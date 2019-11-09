#pragma once

#include <iron.h>
#include <math/vector.h>

ironBEGIN_NAMESPACE

class Entity;

class EntityBuilder
{
public:
    static void BuildFurnace(Entity* entity, const Vector2f& position);
    static void BuildInserter(Entity* entity, const Vector2f& position);
    static void BuildIronOre(Entity* entity, const Vector2f& position);
};

ironEND_NAMESPACE