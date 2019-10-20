#include <iron.h>

#include <ecs/world.h>
#include <ecs/entity.h>
#include <graphics/spritecomponent.h>
#include <graphics/spritesheetmanager.h>
#include <graphics/window.h>
#include <movement/positioncomponent.h>

void ProcessEvents(iron::Window& window)
{
	sf::RenderWindow& renderWindow = window.GetSFMLWindow();

    sf::Event event;
    while (renderWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
			renderWindow.close();
        }
    }
}

void Update(float deltaTime, iron::World& world)
{
	world.Update(deltaTime);
}

void Render(iron::Window& window, iron::World& world)
{
    window.Clear();

	world.Render(&window);

    window.Display();
}

int main()
{
	iron::Window window;
	iron::World world;
	world.GetSpriteSheetManager().LoadSpriteSheet();

	world.CreateSystems();

	iron::Entity* entity = world.CreateEntity();
    entity->AddComponent(new iron::SpriteComponent(12, 2));
    entity->AddComponent(new iron::PositionComponent(0, 0));
	world.RegisterEntity(entity);

    sf::Clock clock;
    sf::Time accumulator = sf::Time::Zero;
    sf::Time ups = sf::seconds(1.f / 60.f);
    float deltaTime = ups.asSeconds();

    while (window.IsOpen())
    {
        ProcessEvents(window);

        while (accumulator > ups)
        {
            accumulator -= ups;
            Update(deltaTime, world);
        }

        Render(window, world);

        accumulator += clock.restart();
    }

    return 0;
}