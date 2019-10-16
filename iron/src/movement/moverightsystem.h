#pragma once

#include <iron.h>
#include <ecs/system.h>
#include <movement/positioncomponent.h>

ironBEGIN_NAMESPACE

class MoveRightSystem : public System
{
public:
	IRON_SYSTEM_1(MoveRightSystemTuple, PositionComponent);

	virtual void Update(float deltaTime) override;
};

ironEND_NAMESPACE