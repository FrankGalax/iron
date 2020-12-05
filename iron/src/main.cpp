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
#include <movement/onbeltcomponent.h>
#include <movement/positioncomponent.h>
#include <movement/insertercomponent.h>

using namespace iron;

void InitEntities(World& world, const Window& window)
{
    Entity* inputEntity = world.CreateEntity();
    EntityBuilder::BuildInputEntity(inputEntity, &window);

    Entity* inserterInTopBelt = world.CreateEntity();
    EntityBuilder::BuildInserter(inserterInTopBelt, Vector2f(6.f, 2.f), Vector2f::Down);

    Entity* inserterInTopBelt1 = world.CreateEntity();
    EntityBuilder::BuildInserter(inserterInTopBelt1, Vector2f(5.f, 3.f), Vector2f::Right);

    Entity* inserterInTopBelt2 = world.CreateEntity();
    EntityBuilder::BuildInserter(inserterInTopBelt2, Vector2f(7.f, 4.f), Vector2f::Left);

    Entity* inserterIn = world.CreateEntity();
    EntityBuilder::BuildInserter(inserterIn, Vector2f(6.f, 7.f), Vector2f::Down);

    Entity* furnace = world.CreateEntity();
    EntityBuilder::BuildFurnace(furnace, Vector2f(6.f, 8.f));

    Entity* inserterOut = world.CreateEntity();
    EntityBuilder::BuildInserter(inserterOut, Vector2f(6.f, 10.f), Vector2f::Down);

    std::vector<Entity*> belts;
    for (int i = 0; i < 5; ++i)
    {
        Entity* belt = world.CreateEntity();
        EntityBuilder::BuildBelt(belt, Vector2f(6.f + (float)i, 11.f), Vector2f::Right);

        belts.push_back(belt);
    }

    Entity* inserterInBottomBelt = world.CreateEntity();
    EntityBuilder::BuildInserter(inserterInBottomBelt, Vector2f(7.f, 12.f), Vector2f::Up);

    for (int i = 0; i < 4; ++i)
    {
        Entity* belt = world.CreateEntity();
        EntityBuilder::BuildBelt(belt, Vector2f(11, 11.f - (float)i), Vector2f::Up);
        
        belts.push_back(belt);
    }

    for (int i = 0; i < 2; ++i)
    {
        Entity* belt = world.CreateEntity();
        EntityBuilder::BuildBelt(belt, Vector2f(11.f - (float)i, 7.f), Vector2f::Left);

        belts.push_back(belt);
    }
    
    for (int i = 0; i < 2; ++i)
    {
        Entity* belt = world.CreateEntity();
        EntityBuilder::BuildBelt(belt, Vector2f(9.f, 7.f + (float)i), Vector2f::Down);

        belts.push_back(belt);
    }

    for (int i = 0; i < belts.size() - 1; ++i)
    {
        belts[i]->GetComponent<BeltComponent>()->SetNextBelt(belts[(size_t)i+1]->GetComponent<BeltComponent>());
    }
    belts.clear();

    for (int i = 0; i < 4; ++i)
    {
        Entity* belt = world.CreateEntity();
        EntityBuilder::BuildBelt(belt, Vector2f(6.f, 3.f + (float)i), Vector2f::Down);

        belts.push_back(belt);

        if (i == 0)
        {
            Entity* ironOre = world.CreateEntity();
            EntityBuilder::BuildIronOre(ironOre, Vector2f(6.f, 3.f));
            OnBeltComponent* onBeltComponent = new OnBeltComponent();
            onBeltComponent->SetBelt(belt->GetComponent<BeltComponent>());
            ironOre->AddComponent(onBeltComponent);
        }
    }

    for (int i = 0; i < belts.size() - 1; ++i)
    {
        belts[i]->GetComponent<BeltComponent>()->SetNextBelt(belts[(size_t)i+1]->GetComponent<BeltComponent>());
    }
    belts.clear();

    Entity* inserter2 = world.CreateEntity();
    EntityBuilder::BuildInserter(inserter2, Vector2f(9.f, 9.f), Vector2f::Down);

    Entity* chest = world.CreateEntity();
    EntityBuilder::BuildChest(chest, Vector2f(9.f, 10.f));
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
    constexpr float maxDeltaTime = 1.f / 60.f;

    while (window.IsOpen())
    {
        ProcessEvents(window);
        deltaTime = clock.restart();
        float deltaTimeSeconds = deltaTime.asSeconds();
        if (deltaTimeSeconds > maxDeltaTime)
        {
            deltaTimeSeconds = maxDeltaTime;
        }

        world.Update(deltaTimeSeconds);
        window.Clear();
        world.Render(&window);

        deltaTimeSum += deltaTimeSeconds;
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