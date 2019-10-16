#include <graphics/window.h>

ironBEGIN_NAMESPACE

Window::Window() :
	m_Window(sf::VideoMode(800, 600), "SFML Test")
{
}

void Window::Draw(const sf::Drawable* drawable)
{
	m_Window.draw(*drawable);
}

ironEND_NAMESPACE