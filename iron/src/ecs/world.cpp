#include <ecs/world.h>
#include <ecs/entity.h>
#include <ecs/system.h>
#include <graphics/animationsystem.h>
#include <graphics/spriterendersystem.h>
#include <graphics/window.h>
#include <movement/beltsystem.h>
#include <item/craftingsystem.h>
#include <item/inventorysystem.h>
#include <movement/insertersystem.h>

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
    m_UpdateSystems.push_back(new InserterSystem());
    m_UpdateSystems.push_back(new CraftingSystem());
    m_UpdateSystems.push_back(new InventorySystem());
    m_UpdateSystems.push_back(new BeltSystem());
    m_UpdateSystems.push_back(new AnimationSystem());
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

void World::AddEntity(Entity* entity)
{
    m_PendingAddEntities.push_back(entity);
}

void World::RemoveEntity(Entity* entity)
{
    m_PendingRemoveEntities.push_back(entity);
}

void World::UnregisterEntity(Entity* entity)
{
    for (System* system : m_UpdateSystems)
    {
        system->UnregisterEntity(entity);
    }

    for (System* system : m_RenderSystems)
    {
        system->UnregisterEntity(entity);
    }
}

void World::Update(float deltaTime)
{
    for (Entity* pendingEntity : m_PendingRemoveEntities)
    {
        for (int i = 0; i < m_Entities.size(); ++i)
        {
            if (m_Entities[i] == pendingEntity)
            {
                m_Entities[i] = m_Entities[m_Entities.size() - 1];
                m_Entities.pop_back();
                UnregisterEntity(pendingEntity);
                delete pendingEntity;
                break;
            }
        }
    }
    m_PendingRemoveEntities.clear();

    for (Entity* pendingEntity : m_PendingAddEntities)
    {
        RegisterEntity(pendingEntity);
    }
    m_PendingAddEntities.clear();

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