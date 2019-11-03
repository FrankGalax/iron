#include <utils.h>
#include <movement/positioncomponent.h>

ironBEGIN_NAMESPACE

bool Utils::IsColliding(PositionComponent* positionComponent, const Vector2f& position)
{
	if (positionComponent == nullptr)
	{
		return false;
	}

	for (int i = 0; i < positionComponent->GetSizeX(); ++i)
	{
		for (int j = 0; j < positionComponent->GetSizeY(); ++j)
		{
			const Vector2f delta = positionComponent->GetPosition() + Vector2f((float)i, (float)j) - position;
			if (delta.IsNull())
			{
				return true;
			}
		}
	}

	return false;
}

ironEND_NAMESPACE