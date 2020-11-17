#pragma once

#include <iron.h>
#include <SFML/Graphics.hpp>

ironBEGIN_NAMESPACE

enum class ButtonType
{
	None,
	X
};

struct Button
{
	ButtonType m_ButtonType = ButtonType::None;
	sf::Sprite m_Sprite;
};

ironEND_NAMESPACE