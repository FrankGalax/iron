#pragma once

#include <iron.h>
#include <ecs/system.h>

ironBEGIN_NAMESPACE

class AnimationComponent;
class SpriteComponent;

class AnimationSystem : public System
{
    IRON_SYSTEM_DECLARE_2(AnimationSystemTuple, AnimationComponent, SpriteComponent);

    virtual void Update(float deltaTime) override;
};

ironEND_NAMESPACE