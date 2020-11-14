#include <input/inputsystem.h>
#include <ecs/world.h>
#include <graphics/uicomponent.h>
#include <graphics/window.h>
#include <input/clickedcomponent.h>
#include <input/inputcomponent.h>
#include <item/inventorycomponent.h>
#include <math/vector.h>
#include <SFML/Window.hpp>
#include <utils.h>
#include <assert.h>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_OR_2(InputSystem, InputSystemTuple, InputComponent, UIComponent);

void InputSystem::Update(float deltaTime)
{
	InputComponent* inputComponent = nullptr;
	UIComponent* uiComponent = nullptr;
	for (InputSystemTuple& tuple : m_Tuples)
	{
		if (tuple.m_InputComponent != nullptr)
		{
			inputComponent = tuple.m_InputComponent;
		}
		if (tuple.m_UIComponent != nullptr)
		{
			uiComponent = tuple.m_UIComponent;
		}
	}

	assert(inputComponent != nullptr);
	assert(uiComponent != nullptr);

	const bool isLeftMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	const bool wasLeftMouseButtonPressed = inputComponent->GetIsLeftMouseButtonPressed();
		
	if (isLeftMouseButtonPressed && !wasLeftMouseButtonPressed)
	{
		const sf::RenderWindow& window = inputComponent->GetWindow()->GetSFMLWindow();
		sf::Vector2i sfPosition = sf::Mouse::getPosition(window);
		if (sfPosition.x >= 0 && sfPosition.x < (int)window.getSize().x && sfPosition.y >= 0 && sfPosition.y < (int)window.getSize().y)
		{
			Vector2f position(sfPosition.x / (GRID_SIZE * RENDER_SCALE), sfPosition.y / (GRID_SIZE * RENDER_SCALE));

			Entity* clickedEntity = Utils::GetEntityAtPosition(inputComponent->GetOwner()->GetWorld(), position);
			Entity* oldClickedEntity = inputComponent->GetClickedEntity();

			if (clickedEntity != oldClickedEntity)
			{
				if (oldClickedEntity != nullptr)
				{
					World* world = oldClickedEntity->GetWorld();
					world->RemoveComponent(oldClickedEntity->GetComponent<ClickedComponent>());
					world->ResetEntity(oldClickedEntity);
				}

				inputComponent->SetClickedEntity(clickedEntity);

				if (clickedEntity != nullptr)
				{
					clickedEntity->AddComponent(new ClickedComponent());
					clickedEntity->GetWorld()->ResetEntity(clickedEntity);

					if (InventoryComponent* inventoryComponent = clickedEntity->GetComponent<InventoryComponent>())
					{
						inventoryComponent->SetIsDirtyForUI(true);
					}
				}

				for (sf::Sprite* sprite : uiComponent->GetInventorySprites())
				{
					delete sprite;
				}
				uiComponent->GetInventorySprites().clear();
			}
		}
	}

	inputComponent->SetIsLeftMouseButtonPressed(isLeftMouseButtonPressed);
}

ironEND_NAMESPACE