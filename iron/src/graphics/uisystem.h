#pragma once

#include <iron.h>
#include <ecs/system.h>

ironBEGIN_NAMESPACE

class UIComponent;
class ClickedComponent;

class UISystem : public System
{
	IRON_SYSTEM_DECLARE_2(UISystemTuple, UIComponent, ClickedComponent);

	virtual void Render(Window* window) override;

private:
	void InitUIComponent(UIComponent* uiComponent);
};

ironEND_NAMESPACE