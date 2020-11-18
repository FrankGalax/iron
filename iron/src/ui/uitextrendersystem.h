#pragma once

#include <iron.h>
#include <ecs/system.h>

ironBEGIN_NAMESPACE

class UITextComponent;
class PositionComponent;

class UITextRenderSystem : public System
{
public:
    IRON_SYSTEM_DECLARE_2(UITextRenderSystemTuple, UITextComponent, PositionComponent);

    virtual void Render(Window* window) override;
};

ironEND_NAMESPACE