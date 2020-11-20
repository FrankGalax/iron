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

void InitEntities(World& world, const Window& window)
{
    Entity* inputEntity = world.CreateEntity();
    EntityBuilder::BuildInputEntity(inputEntity, &window);
    world.RegisterEntity(inputEntity);

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
    for (int i = 0; i < 5; ++i)
    {
        Entity* belt = world.CreateEntity();
        EntityBuilder::BuildBelt(belt, Vector2f((float)i, 5.f), Vector2f::Right);
        world.RegisterEntity(belt);

        belts.push_back(belt);
    }

    for (int i = 0; i < 4; ++i)
    {
        Entity* belt = world.CreateEntity();
        EntityBuilder::BuildBelt(belt, Vector2f(5, 5.f - (float)i), Vector2f::Up);
        world.RegisterEntity(belt);
        
        belts.push_back(belt);
    }

    for (int i = 0; i < 2; ++i)
    {
        Entity* belt = world.CreateEntity();
        EntityBuilder::BuildBelt(belt, Vector2f(5.f - (float)i, 1.f), Vector2f::Left);
        world.RegisterEntity(belt);

        belts.push_back(belt);
    }
    
    for (int i = 0; i < 2; ++i)
    {
        Entity* belt = world.CreateEntity();
        EntityBuilder::BuildBelt(belt, Vector2f(3.f, 1.f + (float)i), Vector2f::Down);
        world.RegisterEntity(belt);

        belts.push_back(belt);
    }

    for (int i = 0; i < belts.size() - 1; ++i)
    {
        belts[i]->GetComponent<BeltComponent>()->SetNextBelt(belts[i+1]->GetComponent<BeltComponent>());
    }

    Entity* inserter2 = world.CreateEntity();
    EntityBuilder::BuildInserter(inserter2, Vector2f(3.f, 3.f));
    world.RegisterEntity(inserter2);

    Entity* chest = world.CreateEntity();
    EntityBuilder::BuildChest(chest, Vector2f(3.f, 4.f));
    world.RegisterEntity(chest);
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

int main()
{
    Window window;
    World world;
    world.GetSpriteSheetManager().LoadSpriteSheet();

    world.CreateSystems();

    InitEntities(world, window);

    sf::Clock clock;
    
    /*sf::Time accumulator = sf::Time::Zero;
    sf::Time ups = sf::seconds(1.f / 60.f);
    float deltaTime = ups.asSeconds();

    int waitInitial = 60;

    while (window.IsOpen())
    {
        ProcessEvents(window);

        while (accumulator > ups)
        {
            accumulator -= ups;

            if (waitInitial > 0)
            {
                waitInitial--;
            }
            else
            {
                Update(deltaTime, world);
            }
        }

        Render(window, world);

        accumulator += clock.restart();
    }*/

    sf::Time deltaTime;
    int fps = 0;
    float deltaTimeSum = 0.f;
    int deltaTimeCount = 0;

    float waitInitial = 1.f;

    sf::Text fpsText;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    fpsText.setFont(font);
    fpsText.setFillColor(sf::Color::Black);
    fpsText.setCharacterSize(15);

    sf::Text entitiesText;
    entitiesText.setFont(font);
    entitiesText.setFillColor(sf::Color::Black);
    entitiesText.setCharacterSize(15);
    entitiesText.setPosition(sf::Vector2f(100, 0));

    while (window.IsOpen())
    {
        ProcessEvents(window);
        deltaTime = clock.restart();
        const float deltaTimeSeconds = deltaTime.asSeconds();

        if (waitInitial > 0)
        {
            waitInitial -= deltaTimeSeconds;
        }
        else
        {
            world.Update(deltaTimeSeconds);
        }

        window.Clear();
        world.Render(&window);

        deltaTimeSum += deltaTime.asSeconds();
        deltaTimeCount++;
        if (deltaTimeSum > 1.f)
        {
            float average = deltaTimeSum / (float)deltaTimeCount;
            fps = (int)(1.f / average);

            deltaTimeSum = 0.f;
            deltaTimeCount = 0;

            fpsText.setString(std::to_string(fps));
        }

        window.Draw(&fpsText);

        entitiesText.setString(std::to_string(world.GetEntities().size()));
        window.Draw(&entitiesText);

        window.Display();
    }

    return 0;
}