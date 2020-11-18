#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <ui/button.h>
#include <SFML/Graphics.hpp>

ironBEGIN_NAMESPACE

class UIButtonComponent : public Component
{
public:
	UIButtonComponent(ButtonType buttonType) : m_ButtonType(buttonType) {}

	ButtonType GetButtonType() const { return m_ButtonType; }

private:
	ButtonType m_ButtonType = ButtonType::None;
};

ironEND_NAMESPACE