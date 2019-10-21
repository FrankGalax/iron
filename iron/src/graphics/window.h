#pragma once

#include <iron.h>
#include <SFML/Graphics.hpp>

ironBEGIN_NAMESPACE

class Window
{
public:
    Window();
    sf::RenderWindow& GetSFMLWindow() { return m_Window; }
    void Clear() { m_Window.clear(sf::Color(200, 200, 200, 255)); }
    void Display() { m_Window.display(); }
    bool IsOpen() const { return m_Window.isOpen(); }
    void Draw(const sf::Drawable* drawable);

private:
    sf::RenderWindow m_Window;
};

ironEND_NAMESPACE