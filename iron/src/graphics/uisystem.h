#pragma once

#include <iron.h>
#include <ecs/system.h>

ironBEGIN_NAMESPACE

class UIComponent;
class ClickedComponent;
class InventoryComponent;

class UISystem : public System
{
	IRON_SYSTEM_DECLARE_2(UISystemTuple, UIComponent, ClickedComponent);

	virtual void Render(Window* window) override;

private:
	void InitBaseSprites(UIComponent* uiComponent);
	void InitInventorySprites(UIComponent* uiComponent, const InventoryComponent* inventoryComponent);
	void DrawInventoryUI(UIComponent* uiComponent, Window* window, float topLeftX, float topLeftY, int sizeX, int sizeY);
};

ironEND_NAMESPACE