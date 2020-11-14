#pragma once

#include <iron.h>
#include <ecs/system.h>

ironBEGIN_NAMESPACE

class InputComponent;
class UIComponent;

class InputSystem : public System
{
	IRON_SYSTEM_DECLARE_2(InputSystemTuple, InputComponent, UIComponent);

	virtual void Update(float deltaTime) override;
};

ironEND_NAMESPACE