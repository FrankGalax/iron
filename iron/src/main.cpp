#include <iron.h>

#include <ecs/world.h>
#include <ecs/entity.h>
#include <graphics/spritecomponent.h>
#include <graphics/spritesheetmanager.h>
#include <graphics/window.h>
#include <item/craftercomponent.h>
#include <item/resourcecomponent.h>
#include <movement/positioncomponent.h>
#include <movement/insertercomponent.h>

using namespace iron;

void InitEntities(iron::World& world)
{
    Entity* ironOre = world.CreateEntity();
    ironOre->SetName("ironOre");
    ironOre->AddComponent(new SpriteComponent(0, 58, 1.f, 1.f));
    ironOre->AddComponent(new PositionComponent(0.f, 0.f));
    ironOre->AddComponent(new InserterComponent(InserterComponent::InserterType::Insertable));
	ironOre->AddComponent(new ResourceComponent(ResourceType::IronOre));
    world.RegisterEntity(ironOre);

    Entity* inserterIn = world.CreateEntity();
    inserterIn->SetName("inserterIn");
    inserterIn->AddComponent(new SpriteComponent(18, 11, 1.f, 1.f));
    inserterIn->AddComponent(new PositionComponent(0.f, 1.f));
    inserterIn->AddComponent(new InserterComponent(InserterComponent::InserterType::Inserter, Vector2f(0.f, -1.f), Vector2f(0.f, 1.f)));
    world.RegisterEntity(inserterIn);

    Entity* furnace = world.CreateEntity();
    furnace->SetName("furnace");
    furnace->AddComponent(new SpriteComponent(12, 2, 2.f, 2.f));
    furnace->AddComponent(new PositionComponent(0.f, 2.f, 2, 2));
    furnace->AddComponent(new InserterComponent(InserterComponent::InserterType::Insertable));
	CrafterComponent* furnaceCrafterComponent = new CrafterComponent();
	std::vector<Recipe>& recipes = furnaceCrafterComponent->GetRecipes();
	{
		Recipe recipe;
		recipe.m_Time = 2.f;
		recipe.m_Product.m_Quantity = 1;
		recipe.m_Product.m_ResourceType = ResourceType::IronIngot;
		RecipeIngredient recipeIngredient;
		recipeIngredient.m_Quantity = 1;
		recipeIngredient.m_ResourceType = ResourceType::IronOre;
		recipe.m_RecipeIngredients.push_back(recipeIngredient);
		recipes.push_back(recipe);
	}
	furnace->AddComponent(furnaceCrafterComponent);
    world.RegisterEntity(furnace);

    Entity* inserterOut = world.CreateEntity();
    inserterOut->SetName("inserterOut");
    inserterOut->AddComponent(new SpriteComponent(18, 11, 1.f, 1.f));
    inserterOut->AddComponent(new PositionComponent(0.f, 4.f));
    inserterOut->AddComponent(new InserterComponent(InserterComponent::InserterType::Inserter, Vector2f(0.f, -1.f), Vector2f(0.f, 1.f)));
    world.RegisterEntity(inserterOut);
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