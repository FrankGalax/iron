#pragma once

#include <iron.h>
#include <ecs/system.h>
#include <item/inventoryitem.h>
#include <ui/button.h>
#include <SFML/Graphics.hpp>

ironBEGIN_NAMESPACE

class InputComponent;
class UIComponent;
class InventoryComponent;

class InputSystem : public System
{
	IRON_SYSTEM_DECLARE_1(InputSystemTuple, InputComponent);

	virtual void Update(float deltaTime) override;

private:
	void GetUICoordonates(const InputComponent* inputComponent, float& topLeftX, float& topLeftY, int& sizeX, int& sizeY) const;
	void AddTitleUI(Entity* entity, float topLeftX, float topLeftY, int sizeX, int sizeY) const;
	void AddInventoryUI(InventoryComponent* inventoryComponent, float topLeftX, float topLeftY, int sizeX, int sizeY) const;
	void RemoveUI(World* world) const;
	void AddUISpriteEntity(World* world, float x, float y, int spriteSheetX, int spriteSheetY, float scaleX, float scaleY, int priority) const;
	void AddUIInventoryEntity(World* world, float x, float y, const InventoryItem& item) const;
	void AddUITextEntity(World* world, float x, float y, const std::string& string, const sf::Color& color, int size) const;
	void AddUIButtonEntity(World* world, float x, float y, ButtonType buttonType) const;
};

ironEND_NAMESPACE