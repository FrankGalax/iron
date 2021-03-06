#pragma once

#include <iron.h>
#include <ecs/system.h>
#include <item/inventoryitem.h>
#include <ui/uienums.h>
#include <SFML/Graphics.hpp>

ironBEGIN_NAMESPACE

class InputComponent;
class UIComponent;
class InventoryComponent;
class CrafterComponent;

class InputSystem : public System
{
	IRON_SYSTEM_DECLARE_2(InputSystemTuple, InputComponent, UIComponent);

	virtual void Update(float deltaTime) override;

private:
	void HandleCurrentClickedEntity(const InputComponent* inputComponent, const UIComponent* uiComponent, Entity* clickedEntity) const;
	void FindClickedEntity(InputComponent* inputComponent, UIComponent* uiComponent) const;
	void HandleKeyPresses(InputComponent* inputComponent) const;
	void AddActionUI(Entity* clickedEntity) const;
	void GetUITopLeft(const InputComponent* inputComponent, int sizeX, int sizeY, float& topLeftX, float& topLeftY) const;
	void AddEntityUI(World* world, const InputComponent* inputComponent, const InventoryComponent* inventoryComponent, const CrafterComponent* crafterComponent) const;
	void AddTitleUI(World* world, const Entity* entity, float topLeftX, float topLeftY, int sizeX, int sizeY) const;
	void AddCrafterUI(World* world, const CrafterComponent* crafterComponent, float topLeftX, float topLeftY, int sizeX, int sizeY) const;
	void AddInventoryUI(World* world, const InventoryComponent* inventoryComponent, float topLeftX, float topLeftY, int sizeX, int sizeY) const;
	void AddSelectionUI(Entity* clickedEntity) const;
	void RemoveUI(World* world) const;
	void AddUISpriteEntity(World* world, float x, float y, int spriteSheetX, int spriteSheetY, float scaleX, float scaleY, float rotation, int priority) const;
	void AddUIInventoryEntity(World* world, float x, float y, const InventoryItem& item) const;
	void AddUITextEntity(World* world, float x, float y, const std::string& string, const sf::Color& color, int size) const;
	void AddUIButtonEntity(World* world, float x, float y, ButtonType buttonType) const;
};

ironEND_NAMESPACE