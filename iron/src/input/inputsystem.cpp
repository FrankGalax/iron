#include <input/inputsystem.h>
#include <graphics/window.h>
#include <input/inputcomponent.h>
#include <math/vector.h>
#include <SFML/Window.hpp>
#include <utils.h>

ironBEGIN_NAMESPACE

IRON_SYSTEM_IMPLEMENT_1(InputSystem, InputSystemTuple, InputComponent);

void InputSystem::Update(float deltaTime)
{
	for (InputSystemTuple& tuple : m_Tuples)
	{
		const bool isLeftMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
		const bool wasLeftMouseButtonPressed = tuple.m_InputComponent->GetIsLeftMouseButtonPressed();
		
		if (isLeftMouseButtonPressed && !wasLeftMouseButtonPressed)
		{
			const sf::RenderWindow& window = tuple.m_InputComponent->GetWindow()->GetSFMLWindow();
			sf::Vector2i sfPosition = sf::Mouse::getPosition(window);
			if (sfPosition.x >= 0 && sfPosition.x < (int)window.getSize().x && sfPosition.y >= 0 && sfPosition.y < (int)window.getSize().y)
			{
				Vector2f position(sfPosition.x / (GRID_SIZE * RENDER_SCALE), sfPosition.y / (GRID_SIZE * RENDER_SCALE));

				tuple.m_InputComponent->SetClickedEntity(Utils::GetEntityAtPosition(tuple.m_Entity->GetWorld(), position));
			}
		}

		tuple.m_InputComponent->SetIsLeftMouseButtonPressed(isLeftMouseButtonPressed);
	}
}

ironEND_NAMESPACE