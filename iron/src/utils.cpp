#include <utils.h>
#include <ecs/world.h>
#include <ecs/entity.h>
#include <movement/positioncomponent.h>
#include <assert.h>

ironBEGIN_NAMESPACE

bool Utils::IsColliding(const PositionComponent* positionComponent, const Vector2f& position)
{
	if (positionComponent == nullptr)
	{
		return false;
	}

    const float minX = positionComponent->GetPosition().GetX();
    const float maxX = minX + positionComponent->GetSizeX();
    const float minY = positionComponent->GetPosition().GetY();
    const float maxY = minY + positionComponent->GetSizeY();

    const float x = position.GetX();
    const float y = position.GetY();

    return ironGreaterOrEqualWithEpsilon(x, minX) && ironLesserWithEpsilon(x, maxX) &&
        ironGreaterOrEqualWithEpsilon(y, minY) && ironLesserWithEpsilon(y, maxY);
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

void Utils::GetEntitiesAtPosition(const World* world, const Vector2f& position, std::vector<Entity*>& entities)
{
    if (world != nullptr)
    {
        for (Entity* entity : world->GetEntities())
        {
            if (const PositionComponent* positionComponent = entity->GetPositionComponent())
            {
                if (IsColliding(positionComponent, position))
                {
                    entities.push_back(entity);
                }
            }
        }
    }
}

ironEND_NAMESPACE