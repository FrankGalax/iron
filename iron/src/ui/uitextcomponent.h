#pragma once

#include <iron.h>
#include <ecs/component.h>
#include <string>
#include <SFML/Graphics.hpp>

ironBEGIN_NAMESPACE

class JSON;

class UITextComponent : public Component
{
public:
    UITextComponent() {}
    UITextComponent(const std::string& string, const sf::Color& color) : m_String(string), m_Color(color), m_Size(20) {}
    UITextComponent(const std::string& string, const sf::Color& color, int size) : m_String(string), m_Color(color), m_Size(size) {}

    const std::string& GetString() const { return m_String; }
    const sf::Color& GetColor() const { return m_Color; }
    int GetSize() const { return m_Size; }

    virtual void ToJSON(JSON* j) override;
    virtual void FromJSON(JSON* j) override;

private:
    std::string m_String;
    sf::Color m_Color;
    int m_Size = 20;

#pragma region usercodeclass
public:
	sf::Text& GetText() { return m_Text; }
	sf::Font& GetFont() { return m_Font; }

private:
	sf::Text m_Text;
	sf::Font m_Font;
#pragma endregion
};

ironEND_NAMESPACE