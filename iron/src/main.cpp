#include <iron.h>

#include <ecs/world.h>
#include <ecs/entity.h>
#include <graphics/spritecomponent.h>
#include <graphics/spritesheetmanager.h>
#include <graphics/window.h>
#include <movement/positioncomponent.h>
#include <movement/positionnotifycomponent.h>

void InitEntities(iron::World& world)
{
    iron::Entity* ironOre = world.CreateEntity();
    ironOre->SetName("ironOre");
    ironOre->AddComponent(new iron::SpriteComponent(0, 58, 1.f, 1.f));
    ironOre->AddComponent(new iron::PositionComponent(0.f, 0.f));
    ironOre->AddComponent(new iron::PositionNotifyComponent(iron::PositionNotifyComponent::NotifyType::Notifier));
    world.RegisterEntity(ironOre);

    iron::Entity* inserterIn = world.CreateEntity();
    inserterIn->SetName("inserterIn");
    inserterIn->AddComponent(new iron::SpriteComponent(18, 11, 1.f, 1.f));
    inserterIn->AddComponent(new iron::PositionComponent(0.f, 1.f));
    inserterIn->AddComponent(new iron::PositionNotifyComponent(iron::PositionNotifyComponent::NotifyType::Listener, iron::Vector2f(0.f, -1.f), iron::Vector2f(0.f, 1.f)));
    world.RegisterEntity(inserterIn);

    iron::Entity* furnace = world.CreateEntity();
    furnace->SetName("furnace");
    furnace->AddComponent(new iron::SpriteComponent(12, 2, 2.f, 2.f));
    furnace->AddComponent(new iron::PositionComponent(0.f, 2.f));
    furnace->AddComponent(new iron::PositionNotifyComponent(iron::PositionNotifyComponent::NotifyType::Notifier));
    world.RegisterEntity(furnace);

    iron::Entity* inserterOut = world.CreateEntity();
    inserterOut->SetName("inserterOut");
    inserterOut->AddComponent(new iron::SpriteComponent(18, 11, 1.f, 1.f));
    inserterOut->AddComponent(new iron::PositionComponent(0.f, 4.f));
    inserterOut->AddComponent(new iron::PositionNotifyComponent(iron::PositionNotifyComponent::NotifyType::Listener, iron::Vector2f(0.f, -1.f), iron::Vector2f(0.f, 1.f)));
    world.RegisterEntity(inserterOut);
}

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

    InitEntities(world);

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