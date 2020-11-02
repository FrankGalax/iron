#pragma once

#include <iron.h>
#include <math/vector.h>
#include <vector>
#include <item/itemenum.h>

ironBEGIN_NAMESPACE
class PositionComponent;

class Utils
{
public:
	static bool IsColliding(const PositionComponent* positionComponent, const Vector2f& position);
    static const char* GetRessourceName(ResourceType resourceType);
};

ironEND_NAMESPACE