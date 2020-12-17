#include <input/inputsystem.h>
#include <data/entitybuilder.h>
#include <ecs/world.h>
#include <graphics/spriteinfo.h>
#include <ui/uibuttoncomponent.h>
#include <ui/uispritecomponent.h>
#include <ui/uitextcomponent.h>
#include <graphics/window.h>
#include <input/inputcomponent.h>
#include <item/craftercomponent.h>
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

	if (inputComponent == nullptr)
	{
		return;
	}

	Entity* currentClickedEntity = inputComponent->GetClickedEntity();
	if (currentClickedEntity != nullptr)
	{
		if (InventoryComponent* inventoryComponent = currentClickedEntity->GetComponent<InventoryComponent>())
		{
			if (inventoryComponent->GetIsDirtyForUI())
			{
				inventoryComponent->SetIsDirtyForUI(false);

				CrafterComponent* crafterComponent = currentClickedEntity->GetComponent<CrafterComponent>();

				World* world = inventoryComponent->GetOwner()->GetWorld();
				RemoveUI(world);
				AddEntityUI(world, inputComponent, inventoryComponent, crafterComponent);
			}
		}
	}

	const bool isLeftMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	const bool wasLeftMouseButtonPressed = inputComponent->GetIsLeftMouseButtonPressed();

	if (isLeftMouseButtonPressed && !wasLeftMouseButtonPressed)
	{
		const sf::RenderWindow& window = inputComponent->GetOwner()->GetWorld()->GetWindow()->GetSFMLWindow();
		sf::Vector2i sfPosition = sf::Mouse::getPosition(window);
		if (sfPosition.x >= 0 && sfPosition.x < (int)window.getSize().x && sfPosition.y >= 0 && sfPosition.y < (int)window.getSize().y)
		{
			Vector2f position(sfPosition.x / (GRID_SIZE * RENDER_SCALE), sfPosition.y / (GRID_SIZE * RENDER_SCALE));

			std::vector<Entity*> clickedEntities;
			Utils::GetEntitiesAtPosition(inputComponent->GetOwner()->GetWorld(), position, Vector2f::Zero, clickedEntities);
			if (clickedEntities.empty())
			{
				Vector2f gridPosition(floor(position.GetX()), floor(position.GetY()));
				World* world = inputComponent->GetOwner()->GetWorld();
				Entity* entity = world->CreateEntity();
				EntityBuilder::BuildFromResource(entity, gridPosition, ResourceType::IronOre);
			}
			else
			{
				for (Entity* clickedEntity : clickedEntities)
				{
					if (UIButtonComponent* uiButtonComponent = clickedEntity->GetComponent<UIButtonComponent>())
					{
						if (uiButtonComponent->GetButtonType() == ButtonType::X)
						{
							RemoveUI(clickedEntity->GetWorld());
							inputComponent->SetClickedEntity(nullptr);
						}
					}
					else if (currentClickedEntity == nullptr)
					{
						if (const InventoryComponent* inventoryComponent = clickedEntity->GetComponent<InventoryComponent>())
						{
							const CrafterComponent* crafterComponent = clickedEntity->GetComponent<CrafterComponent>();

							AddEntityUI(clickedEntity->GetWorld(), inputComponent, inventoryComponent, crafterComponent);

							currentClickedEntity = clickedEntity;
							inputComponent->SetClickedEntity(clickedEntity);
						}
					}
				}
			}
		}
	}

	inputComponent->SetWasLeftMouseButtonPressed(wasLeftMouseButtonPressed);
	inputComponent->SetIsLeftMouseButtonPressed(isLeftMouseButtonPressed);

	const bool isSPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
	const bool isLPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L);
	const bool isCPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C);

	if (isSPressed && !inputComponent->GetIsSPressed())
	{
		inputComponent->GetOwner()->GetWorld()->SetSaveGame(true);
	}

	if (isLPressed && !inputComponent->GetIsLPressed())
	{
		inputComponent->GetOwner()->GetWorld()->SetLoadGame(true);
	}

	if (isCPressed && !inputComponent->GetIsCPressed())
	{
		inputComponent->GetOwner()->GetWorld()->SetClearGame(true);
	}

	inputComponent->SetIsSPressed(isSPressed);
	inputComponent->SetIsLPressed(isLPressed);
	inputComponent->SetIsCPressed(isCPressed);
}

void InputSystem::GetUITopLeft(const InputComponent* inputComponent, int sizeX, int sizeY, float& topLeftX, float& topLeftY) const
{
	const sf::RenderWindow& window = inputComponent->GetOwner()->GetWorld()->GetWindow()->GetSFMLWindow();
	const float screenSizeX = window.getSize().x / (float)(GRID_SIZE * RENDER_SCALE);
	const float screenSizeY = window.getSize().y / (float)(GRID_SIZE * RENDER_SCALE);
	const int fullSizeX = sizeX + 2;
	const int fullSizeY = sizeY + 2;
	topLeftX = screenSizeX / 2.f - fullSizeX / 2.f;
	topLeftY = screenSizeY / 2.f - fullSizeY / 2.f;
}

void InputSystem::AddEntityUI(World* world, const InputComponent* inputComponent, const InventoryComponent* inventoryComponent, const CrafterComponent* crafterComponent) const
{
	const int sizeX = 10;
	const int sectionSizeY = 3;
	const int sizeY = crafterComponent != nullptr ? sectionSizeY * 2 : sectionSizeY;
	float topLeftX;
	float topLeftY;
	GetUITopLeft(inputComponent, sizeX, sizeY, topLeftX, topLeftY);

	AddTitleUI(world, inventoryComponent->GetOwner(), topLeftX, topLeftY, sizeX, sizeY);
	if (crafterComponent != nullptr)
	{
		AddCrafterUI(world, crafterComponent, topLeftX + 1.f, topLeftY + 1.f, sizeX, sectionSizeY);
	}
	AddInventoryUI(world, inventoryComponent, topLeftX + 1.f, topLeftY + 1.f + (crafterComponent != nullptr ? sectionSizeY : 0), sizeX, sectionSizeY);
}

void InputSystem::AddTitleUI(World* world, const Entity* entity, float topLeftX, float topLeftY, int sizeX, int sizeY) const
{
	AddUISpriteEntity(world, topLeftX, topLeftY, 24, 10, 1.f, 1.f, 1); // title top left
	AddUISpriteEntity(world, topLeftX + sizeX + 2.f, topLeftY, 24, 10, -1, 1.f, 1); // title top right

	AddUISpriteEntity(world, topLeftX + 1.f, topLeftY, 24, 11, (float)sizeX, 1.f, 0); // title top
	AddUISpriteEntity(world, topLeftX + 1.f, topLeftY, 24, 8, (float)sizeX, 1.f, 1); // border top
	AddUISpriteEntity(world, topLeftX + 1.f, topLeftY + sizeY + 2.f, 24, 8, (float)sizeX, -1.f, 0); // border bottom

	AddUITextEntity(world, topLeftX + 1.f, topLeftY + 0.1f, entity->GetName(), sf::Color::Black, 20);
	AddUIButtonEntity(world, topLeftX + sizeX, topLeftY, ButtonType::X);

	AddUISpriteEntity(world, topLeftX, topLeftY + 1.f, 24, 7, 1.f, (float)sizeY, 0); // border left
	AddUISpriteEntity(world, topLeftX + sizeX + 2.f, topLeftY + 1.f, 24, 7, -1.f, (float)sizeY, 0); // border right

	AddUISpriteEntity(world, topLeftX, topLeftY, 24, 6, 1.f, 1.f, 2); // border top left
	AddUISpriteEntity(world, topLeftX, topLeftY + sizeY + 2.f, 24, 6, 1.f, -1.f, 0); // border top right
	AddUISpriteEntity(world, topLeftX + sizeX + 2.f, topLeftY + sizeY + 2.f, 24, 6, -1.f, -1.f, 0); // border bottom right
	AddUISpriteEntity(world, topLeftX + sizeX + 2.f, topLeftY, 24, 6, -1.f, 1.f, 2); // border bottom left
}

void InputSystem::AddCrafterUI(World* world, const CrafterComponent* crafterComponent, float topLeftX, float topLeftY, int sizeX, int sizeY) const
{
	const float midSizeX = (sizeX - 1) / 2.f;
	const float midSizeY = (sizeY - 1) / 2.f;

	AddUISpriteEntity(world, topLeftX, topLeftY, 24, 13, (float)sizeX, (float)sizeY, 0);
	AddUISpriteEntity(world, topLeftX + midSizeX - 1.f, topLeftY + midSizeY, 24, 9, 1.f, 1.f, 1);
	AddUISpriteEntity(world, topLeftX + midSizeX + 1.f, topLeftY + midSizeY, 24, 9, 1.f, 1.f, 1);

	if (const Recipe* recipe = crafterComponent->GetActiveRecipe())
	{
		AddUIInventoryEntity(world, topLeftX + midSizeX - 1.f, topLeftY + midSizeY, recipe->GetRecipeIngredients()[0]);
		AddUIInventoryEntity(world, topLeftX + midSizeX + 1.f, topLeftY + midSizeY, recipe->GetProduct());
	}
}

void InputSystem::AddInventoryUI(World* world, const InventoryComponent* inventoryComponent, float topLeftX, float topLeftY, int sizeX, int sizeY) const
{
	for (int i = 0; i < sizeX; ++i)
	{
		for (int j = 0; j < sizeY; ++j)
		{
			AddUISpriteEntity(world, topLeftX + i, topLeftY + j, 24, 9, 1.f, 1.f, 0);
		}
	}

	const std::vector<InventoryItem>& items = inventoryComponent->GetItems();
	for (int i = 0; i < items.size(); ++i)
	{
		const int row = i / sizeX;
		const int column = i % sizeX;
		AddUIInventoryEntity(world, topLeftX + column, topLeftY + row, items[i]);
	}
}

void InputSystem::RemoveUI(World* world) const
{
	for (Entity* entity : world->GetEntities())
	{
		if (entity->GetComponent<UISpriteComponent>() != nullptr ||
			entity->GetComponent<UITextComponent>() != nullptr)
		{
			world->DestroyEntity(entity);
		}
	}
}

void InputSystem::AddUISpriteEntity(World* world, float x, float y, int spriteSheetX, int spriteSheetY, float scaleX, float scaleY, int priority) const
{
	Entity* entity = world->CreateEntity();
	entity->AddComponent(new PositionComponent(Vector2f(x, y)));
	entity->AddComponent(new UISpriteComponent(spriteSheetX, spriteSheetY, scaleX, scaleY, priority));
}

void InputSystem::AddUIInventoryEntity(World* world, float x, float y, const InventoryItem& item) const
{
	Entity* entity = world->CreateEntity();
	entity->AddComponent(new PositionComponent(Vector2f(x, y)));
	SpriteInfo spriteInfo;
	EntityBuilder::BuildSpriteInfoFromResource(spriteInfo, item.GetResourceType());
	entity->AddComponent(new UISpriteComponent(spriteInfo));

	float offset = 0.f;
	if (item.GetQuantity() >= 10)
	{
		offset = 0.45f;
	}
	else
	{
		offset = 0.7f;
	}
	AddUITextEntity(world, x + offset, y + 0.45f, std::to_string(item.GetQuantity()), sf::Color::White, 14);
}

void InputSystem::AddUITextEntity(World* world, float x, float y, const std::string& string, const sf::Color& color, int size) const
{
	Entity* entity = world->CreateEntity();
	entity->AddComponent(new PositionComponent(Vector2f(x, y)));
	entity->AddComponent(new UITextComponent(string, color, size));
}

void InputSystem::AddUIButtonEntity(World* world, float x, float y, ButtonType buttonType) const
{
	Entity* entity = world->CreateEntity();
	entity->AddComponent(new PositionComponent(Vector2f(x, y)));
	entity->AddComponent(new UISpriteComponent(24, 12, 1.f, 1.f, 5));
	entity->AddComponent(new UIButtonComponent(buttonType));
}

ironEND_NAMESPACE