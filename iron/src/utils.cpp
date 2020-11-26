#include <utils.h>
#include <ecs/world.h>
#include <ecs/entity.h>
#include <movement/positioncomponent.h>
#include <assert.h>

ironBEGIN_NAMESPACE

bool Utils::IsColliding(const PositionComponent* positionComponent, const Vector2f& position, const Vector2f& size)
{
	if (positionComponent == nullptr)
	{
		return false;
	}

    const float aMinX = positionComponent->GetPosition().GetX();
    const float aMaxX = aMinX + positionComponent->GetSize().GetX();
    const float aMinY = positionComponent->GetPosition().GetY();
    const float aMaxY = aMinY + positionComponent->GetSize().GetY();

    const float bMinX = position.GetX();
    const float bMaxX = bMinX + size.GetX();
    const float bMinY = position.GetY();
    const float bMaxY = bMinY + size.GetY();

    return aMinX < bMaxX && aMaxX > bMinX && aMinY < bMaxY && aMaxY > bMinY;
}

const char* Utils::GetRessourceName(ResourceType resourceType)
{
    switch (resourceType)
    {
    case ResourceType::None:
        return "None";
    case ResourceType::IronOre:
        return "IronOre";
    case ResourceType::IronIngot:
        return "IronIngot";
    }

    assert(false);
    return "";
}

void Utils::GetEntitiesAtPosition(const World* world, const Vector2f& position, const Vector2f& size, std::vector<Entity*>& entities)
{
    if (world != nullptr)
    {
        for (Entity* entity : world->GetEntities())
        {
            if (const PositionComponent* positionComponent = entity->GetPositionComponent())
            {
                if (IsColliding(positionComponent, position, size))
                {
                    entities.push_back(entity);
                }
            }
        }
    }
}

ironEND_NAMESPACE