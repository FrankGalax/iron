#include <ecs/world.h>
#include <ecs/entity.h>
#include <ecs/system.h>
#include <graphics/spriterendersystem.h>
#include <graphics/window.h>
#include <item/beltsystem.h>
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
    int i = 0;
    while (i < m_Entities.size())
    {
        Entity* entity = m_Entities[i];
        if (entity->GetWorld() == nullptr)
        {
            m_Entities[i] = m_Entities[m_Entities.size() - 1];
            m_Entities.pop_back();
            UnregisterEntity(entity);
            delete entity;
        }
        else
        {
            i++;
        }
    }

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