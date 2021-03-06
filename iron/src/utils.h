#pragma once

#include <iron.h>
#include <math/vector.h>
#include <vector>
#include <item/itemenum.h>

ironBEGIN_NAMESPACE
class PositionComponent;
class World;
class Entity;

class Utils
{
public:
	static bool IsColliding(const PositionComponent* positionComponent, const Vector2f& position, const Vector2f& size);
    static const char* GetRessourceName(ResourceType resourceType);
    static void GetEntitiesAtPosition(const World* world, const Vector2f& position, const Vector2f& size, std::vector<Entity*>& entities);
};

ironEND_NAMESPACE