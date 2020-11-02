#include <iron.h>

#include <data/entitybuilder.h>
#include <ecs/world.h>
#include <ecs/entity.h>
#include <graphics/spritecomponent.h>
#include <graphics/spritesheetmanager.h>
#include <graphics/window.h>
#include <item/craftercomponent.h>
#include <item/inventorycomponent.h>
#include <item/resourcecomponent.h>
#include <movement/beltcomponent.h>
#include <movement/positioncomponent.h>
#include <movement/insertercomponent.h>

using namespace iron;

void InitEntities(World& world)
{
    Entity* ironOre = world.CreateEntity();
    EntityBuilder::BuildIronOre(ironOre, Vector2f(0.f, 0.f));
    world.RegisterEntity(ironOre);

    Entity* inserterIn = world.CreateEntity();
    EntityBuilder::BuildInserter(inserterIn, Vector2f(0.f, 1.f));
    world.RegisterEntity(inserterIn);

    Entity* furnace = world.CreateEntity();
    EntityBuilder::BuildFurnace(furnace, Vector2f(0.f, 2.f));
    world.RegisterEntity(furnace);

    Entity* inserterOut = world.CreateEntity();
    EntityBuilder::BuildInserter(inserterOut, Vector2f(0.f, 4.f));
    world.RegisterEntity(inserterOut);

    std::vector<Entity*> belts;
    for (int i = 0; i < 10; ++i)
    {
        Entity* belt = world.CreateEntity();
        EntityBuilder::BuildBelt(belt, Vector2f((float)i, 5.f));
        world.RegisterEntity(belt);

        belts.push_back(belt);

        if (i > 0)
        {
            Entity* previousBelt = belts[i - 1];
            BeltComponent* beltComponent = previousBelt->GetComponent<BeltComponent>();
            beltComponent->SetNextBelt(belt->GetComponent<BeltComponent>());
        }
    }

}

void ProcessEvents(Window& window)
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

void Update(float deltaTime, World& world)
{
    world.Update(deltaTime);
}

void Render(Window& window, World& world)
{
    window.Clear();

    world.Render(&window);

    window.Display();
}

int main()
{
    Window window;
    World world;
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