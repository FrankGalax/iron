#pragma once

#include <iron.h>
#include <ecs/system.h>

ironBEGIN_NAMESPACE

class UIComponent;
class ClickedComponent;
class InventoryComponent;
class InputComponent;

class UISystem : public System
{
	IRON_SYSTEM_DECLARE_3(UISystemTuple, UIComponent, ClickedComponent, InputComponent);

	virtual void Update(float deltaTime) override;
	virtual void Render(Window* window) override;

private:
	void InitBaseSprites(UIComponent* uiComponent);
	void InitInventorySprites(UIComponent* uiComponent, const InventoryComponent* inventoryComponent);
	void DrawInventoryUI(UIComponent* uiComponent, const InventoryComponent* inventoryComponent, Window* window, float topLeftX, 
		float topLeftY, int sizeX, int sizeY);
};

ironEND_NAMESPACE