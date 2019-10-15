#include <SFML/Graphics.hpp>

void Init(sf::CircleShape& shape)
{
    shape.setFillColor(sf::Color::Green);
}

void ProcessEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void Update(sf::CircleShape& shape, float deltaTime)
{
    sf::Vector2f speed(50.f, 10.f);
    shape.setPosition(shape.getPosition() + speed * deltaTime);
}

void Render(sf::CircleShape& shape, sf::RenderWindow& window)
{
    window.clear();
    window.draw(shape);
    window.display();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test");
    sf::CircleShape shape(100.f);

    Init(shape);

    sf::Clock clock;
    sf::Time accumulator = sf::Time::Zero;
    sf::Time ups = sf::seconds(1.f / 60.f);
    float deltaTime = ups.asSeconds();

    while (window.isOpen())
    {
        ProcessEvents(window);

        while (accumulator > ups)
        {
            accumulator -= ups;
            Update(shape, deltaTime);
        }

        Render(shape, window);

        accumulator += clock.restart();
    }

    return 0;
}