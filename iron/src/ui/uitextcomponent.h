#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <SFML/Graphics.hpp>
#include <string>

ironBEGIN_NAMESPACE

class UITextComponent : public Component
{
public:
	UITextComponent(const std::string& string, const sf::Color& color, int size) : m_String(string), m_Color(color), m_Size(size) {}

	sf::Text& GetText() { return m_Text; }
	const std::string& GetString() const { return m_String; }
	const sf::Color& GetColor() const { return m_Color; }
	int GetSize() const { return m_Size; }
	sf::Font& GetFont() { return m_Font; }

private:
	sf::Text m_Text;
	std::string m_String;
	sf::Color m_Color;
	sf::Font m_Font;
	int m_Size = 20;
};

ironEND_NAMESPACE