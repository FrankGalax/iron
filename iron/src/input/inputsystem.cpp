#include <input/inputsystem.h>
#include <data/entitybuilder.h>
#include <ecs/world.h>
#include <graphics/spriteinfo.h>
#include <ui/uibuttoncomponent.h>
#include <ui/uispritecomponent.h>
#include <ui/uitextcomponent.h>
#include <graphics/window.h>
#include <input/inputcomponent.h>
#include <item/inventorycomponent.h>
#include <math/vector.h>
#include <movement/positioncomponent.h>
#include <SFML/Window.hpp>
#include <utils.h>
#include <assert.h>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_1(InputSystem, InputSystemTuple, InputComponent);

void InputSystem::Update(float deltaTime)
{
	InputComponent* inputComponent = nullptr;
	for (InputSystemTuple& tuple : m_Tuples)
	{
		if (tuple.m_InputComponent != nullptr)
		{
			inputComponent = tuple.m_InputComponent;
		}
	}

	assert(inputComponent != nullptr);

	const bool isLeftMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	const bool wasLeftMouseButtonPressed = inputComponent->GetIsLeftMouseButtonPressed();

	Entity* currentClickedEntity = inputComponent->GetClickedEntity();
	if (currentClickedEntity != nullptr)
	{
		if (InventoryComponent* inventoryComponent = currentClickedEntity->GetComponent<InventoryComponent>())
		{
			if (inventoryComponent->GetIsDirtyForUI())
			{
				RemoveInventoryUI(inventoryComponent->GetOwner()->GetWorld());
				AddInventoryUI(inventoryComponent, inputComponent->GetWindow());

				inventoryComponent->SetIsDirtyForUI(false);
			}
		}
	}

	if (isLeftMouseButtonPressed && !wasLeftMouseButtonPressed)
	{
		const sf::RenderWindow& window = inputComponent->GetWindow()->GetSFMLWindow();
		sf::Vector2i sfPosition = sf::Mouse::getPosition(window);
		if (sfPosition.x >= 0 && sfPosition.x < (int)window.getSize().x && sfPosition.y >= 0 && sfPosition.y < (int)window.getSize().y)
		{
			Vector2f position(sfPosition.x / (GRID_SIZE * RENDER_SCALE), sfPosition.y / (GRID_SIZE * RENDER_SCALE));

			std::vector<Entity*> clickedEntities;
			Utils::GetEntitiesAtPosition(inputComponent->GetOwner()->GetWorld(), position, clickedEntities);
			for (Entity* clickedEntity : clickedEntities)
			{
				if (UIButtonComponent* uiButtonComponent = clickedEntity->GetComponent<UIButtonComponent>())
				{
					if (uiButtonComponent->GetButtonType() == ButtonType::X)
					{
						RemoveInventoryUI(clickedEntity->GetWorld());
						inputComponent->SetClickedEntity(nullptr);
					}
				}
				else if (currentClickedEntity == nullptr)
				{
					if (InventoryComponent* inventoryComponent = clickedEntity->GetComponent<InventoryComponent>())
					{
						currentClickedEntity = clickedEntity;
						inputComponent->SetClickedEntity(clickedEntity);

						AddInventoryUI(inventoryComponent, inputComponent->GetWindow());
					}
				}
			}
		}
	}

	inputComponent->SetWasLeftMouseButtonPressed(wasLeftMouseButtonPressed);
	inputComponent->SetIsLeftMouseButtonPressed(isLeftMouseButtonPressed);
}

void InputSystem::AddInventoryUI(InventoryComponent* inventoryComponent, const Window* window) const
{
	const int sizeX = 10;
	const int sizeY = 3;
	const float screenSizeX = window->GetSFMLWindow().getSize().x / (float)(GRID_SIZE * RENDER_SCALE);
	const float screenSizeY = window->GetSFMLWindow().getSize().y / (float)(GRID_SIZE * RENDER_SCALE);
	const int fullSizeX = sizeX + 2;
	const int fullSizeY = sizeY + 2;
	const float topLeftX = screenSizeX / 2.f - fullSizeX / 2.f;
	const float topLeftY = screenSizeY / 2.f - fullSizeY / 2.f;

	World* world = inventoryComponent->GetOwner()->GetWorld();
	AddUISpriteEntity(world, topLeftX, topLeftY, 24, 10, 1.f, 1.f, 1);
	AddUISpriteEntity(world, topLeftX + sizeX + 2.f, topLeftY, 24, 10, -1, 1.f, 1);

	for (float i = 0; i < sizeX; i += 1.f)
	{
		AddUISpriteEntity(world, topLeftX + i + 1.f, topLeftY, 24, 11, 1.f, 1.f, 0);
		AddUISpriteEntity(world, topLeftX + i + 1.f, topLeftY, 24, 8, 1.f, 1.f, 1);
		AddUISpriteEntity(world, topLeftX + i + 1.f, topLeftY + sizeY + 2.f, 24, 8, 1.f, -1.f, 0);
	}

	AddUITextEntity(world, topLeftX + 1.f, topLeftY + 0.1f, inventoryComponent->GetOwner()->GetName(), sf::Color::Black, 20);
	AddUIButtonEntity(world, topLeftX + sizeX, topLeftY, ButtonType::X);

	for (float i = 0; i < sizeY; i += 1.f)
	{
		AddUISpriteEntity(world, topLeftX, topLeftY + i + 1.f, 24, 7, 1.f, 1.f, 0);
		AddUISpriteEntity(world, topLeftX + sizeX + 2.f, topLeftY + i + 1.f, 24, 7, -1.f, 1.f, 0);
	}

	AddUISpriteEntity(world, topLeftX, topLeftY, 24, 6, 1.f, 1.f, 2);
	AddUISpriteEntity(world, topLeftX, topLeftY + sizeY + 2.f, 24, 6, 1.f, -1.f, 0);
	AddUISpriteEntity(world, topLeftX + sizeX + 2.f, topLeftY + sizeY + 2.f, 24, 6, -1.f, -1.f, 0);
	AddUISpriteEntity(world, topLeftX + sizeX + 2.f, topLeftY, 24, 6, -1.f, 1.f, 2);

	for (int i = 0; i < sizeX; ++i)
	{
		for (int j = 0; j < sizeY; ++j)
		{
			AddUISpriteEntity(world, topLeftX + i + 1.f, topLeftY + j + 1.f, 24, 9, 1.f, 1.f, 0);
		}
	}

	const std::vector<InventoryItem>& items = inventoryComponent->GetItems();
	for (int i = 0; i < items.size(); ++i)
	{
		const int row = i / sizeX;
		const int column = i % sizeX;
		AddUIInventoryEntity(world, topLeftX + column + 1.f, topLeftY + row + 1.f, items[i]);
	}
}

void InputSystem::RemoveInventoryUI(World* world) const
{
	for (Entity* entity : world->GetEntities())
	{
		if (entity->GetComponent<UISpriteComponent>() != nullptr ||
			entity->GetComponent<UITextComponent>() != nullptr)
		{
			world->RemoveEntity(entity);
		}
	}
}

void InputSystem::AddUISpriteEntity(World* world, float x, float y, int spriteSheetX, int spriteSheetY, float scaleX, float scaleY, int priority) const
{
	Entity* entity = world->CreateEntity();
	entity->AddComponent(new PositionComponent(Vector2f(x, y), 1, 1));
	entity->AddComponent(new UISpriteComponent(spriteSheetX, spriteSheetY, scaleX, scaleY, priority));
	world->RegisterEntity(entity);
}

void InputSystem::AddUIInventoryEntity(World* world, float x, float y, const InventoryItem& item) const
{
	Entity* entity = world->CreateEntity();
	entity->AddComponent(new PositionComponent(Vector2f(x, y), 1, 1));
	SpriteInfo spriteInfo;
	EntityBuilder::BuildSpriteInfoFromResource(spriteInfo, item.m_ResourceType);
	entity->AddComponent(new UISpriteComponent(spriteInfo));
	world->RegisterEntity(entity);

	AddUITextEntity(world, x + 0.7f, y + 0.45f, std::to_string(item.m_Quantity), sf::Color::White, 14);
}

void InputSystem::AddUITextEntity(World* world, float x, float y, const std::string& string, const sf::Color& color, int size) const
{
	Entity* entity = world->CreateEntity();
	entity->AddComponent(new PositionComponent(Vector2f(x, y), 1, 1));
	entity->AddComponent(new UITextComponent(string, color, size));
	world->RegisterEntity(entity);
}

void InputSystem::AddUIButtonEntity(World* world, float x, float y, ButtonType buttonType) const
{
	Entity* entity = world->CreateEntity();
	entity->AddComponent(new PositionComponent(Vector2f(x, y), 1, 1));
	entity->AddComponent(new UISpriteComponent(24, 12, 1.f, 1.f, 5));
	entity->AddComponent(new UIButtonComponent(buttonType));
	world->RegisterEntity(entity);
}

ironEND_NAMESPACE