#include <ecs/world.h>
#include <json.h>

#pragma region usercode
#include <ecs/entity.h>
#include <ecs/system.h>
#include <graphics/animationsystem.h>
#include <graphics/spriterendersystem.h>
#include <ui/uirendersystem.h>
#include <ui/uitextrendersystem.h>
#include <graphics/window.h>
#include <input/inputsystem.h>
#include <item/craftingsystem.h>
#include <item/inventorysystem.h>
#include <movement/beltsystem.h>
#include <movement/insertersystem.h>
#pragma endregion

ironBEGIN_NAMESPACE

void World::ToJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    j["class"] = 391991650;
    for (Entity* entitie : m_Entities)
    {
        JSON subJSON;
        entitie->ToJSON(&subJSON);
        j["entities"].push_back(subJSON.GetJ());
    }
}

#pragma region usercodenamespace
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
    m_UpdateSystems.push_back(new InputSystem());
    m_UpdateSystems.push_back(new InserterSystem());
    m_UpdateSystems.push_back(new CraftingSystem());
    m_UpdateSystems.push_back(new InventorySystem());
    m_UpdateSystems.push_back(new BeltSystem());
    m_UpdateSystems.push_back(new AnimationSystem());
    m_RenderSystems.push_back(new SpriteRenderSystem());
    m_RenderSystems.push_back(new UIRenderSystem());
    m_RenderSystems.push_back(new UITextRenderSystem());
}

Entity* World::CreateEntity()
{
    Entity* entity = new Entity(m_NextEntityId++, this);
    m_PendingAddEntities.push_back(entity);
    return entity;
}

void World::DestroyEntity(Entity* entity)
{
    m_PendingRemoveEntities.push_back(entity);
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
        m_Entities.push_back(pendingEntity);
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

void World::RegisterEntity(Entity* entity)
{
    entity->ResetComponentCaches();

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
#pragma endregion

ironEND_NAMESPACE