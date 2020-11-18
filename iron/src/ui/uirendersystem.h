#pragma once

#include <iron.h>
#include <ecs/system.h>

ironBEGIN_NAMESPACE

class UISpriteComponent;
class PositionComponent;

class UIRenderSystem : public System
{
public:
    IRON_SYSTEM_DECLARE_2(UIRenderSystemTuple, UISpriteComponent, PositionComponent);

    virtual void Render(Window* window) override;
};

ironEND_NAMESPACE