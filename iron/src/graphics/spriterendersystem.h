#pragma once

#include <iron.h>
#include <ecs/system.h>

ironBEGIN_NAMESPACE

class SpriteComponent;
class PositionComponent;

class SpriteRenderSystem : public System
{
public:
	IRON_SYSTEM_DECLARE_2(SpriteRenderSystemTuple, SpriteComponent, PositionComponent)

	virtual void Render(Window* window) override;
};

ironEND_NAMESPACE