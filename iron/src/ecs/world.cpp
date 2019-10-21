#include <ecs/world.h>
#include <ecs/entity.h>
#include <ecs/system.h>
#include <graphics/spriterendersystem.h>
#include <graphics/window.h>
#include <movement/positionnotifysystem.h>

ironBEGIN_NAMESPACE

World::~World()
{
    for (System* system : m_UpdateSystems)
    {
        delete system;
    }

    for (System* system : m_RenderSystems)
    {
        delete system;
    }

    for (Entity* entity : m_Entities)
    {
        delete entity;
    }
}

void World::CreateSystems()
{
    m_UpdateSystems.push_back(new PositionNotifySystem());
    m_RenderSystems.push_back(new SpriteRenderSystem());
}

Entity* World::CreateEntity()
{
    Entity* entity = new Entity(m_NextEntityId++, this);
    m_Entities.push_back(entity);
    return entity;
}

void World::RegisterEntity(Entity* entity)
{
    for (System* system : m_UpdateSystems)
    {
        system->RegisterEntity(entity);
    }

    for (System* system : m_RenderSystems)
    {
        system->RegisterEntity(entity);
    }
}

void World::Update(float deltaTime)
{
    for (System* system : m_UpdateSystems)
    {
        system->Update(deltaTime);
    }
}

void World::Render(Window* window)
{
    for (System* system : m_RenderSystems)
    {
        system->Render(window);
    }
}

ironEND_NAMESPACE