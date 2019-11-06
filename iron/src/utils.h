#pragma once

#include <iron.h>
#include <math/vector.h>
#include <vector>

ironBEGIN_NAMESPACE
class PositionComponent;

class Utils
{
public:
	static bool IsColliding(PositionComponent* positionComponent, const Vector2f& position);
};

ironEND_NAMESPACE