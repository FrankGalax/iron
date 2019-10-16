#pragma once

#include <iron.h>
#include <ecs/system.h>
#include <graphics/sfmlcirclecomponent.h>
#include <movement/positioncomponent.h>

ironBEGIN_NAMESPACE

class SFMLCircleRenderSystem : public System
{
public:
	IRON_SYSTEM_DECLARE_2(SFMLCircleRenderSystemTuple, SFMLCircleComponent, PositionComponent)

protected:
	virtual void Render(Window* window) override;
};

ironEND_NAMESPACE