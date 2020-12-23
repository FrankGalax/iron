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
#include <input/inputcomponent.h>
#include <input/inputsystem.h>
#include <item/craftingsystem.h>
#include <item/inventorysystem.h>
#include <movement/beltsystem.h>
#include <movement/insertersystem.h>
#include <movement/pathsystem.h>
#include <json.h>
#include <fstream>
#include <iomanip>
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

void World::FromJSON(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    for (nlohmann::json& entitieJ : j["entities"])
    {
        Entity* entitie = new Entity(entitieJ["id"], this);
        JSON entitieJSON(entitieJ);
        entitie->FromJSON(&entitieJSON);
        m_Entities.push_back(entitie);
    }
}

void World::FromJSONResolve(JSON* json)
{
    nlohmann::json& j = json->GetJ();
    for (int i = 0; i < m_Entities.size(); ++i)
    {
        JSON entitieJSON(j["entities"][i]);
        m_Entities[i]->FromJSONResolve(&entitieJSON);
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
    m_UpdateSystems.push_back(new PathSystem());
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
    if (m_ClearGame)
    {
        for (int i = (int)m_Entities.size() - 1; i >= 0; --i)
        {
            Entity* entity = m_Entities[i];
            if (entity->GetComponent<InputComponent>() == nullptr)
            {
                UnregisterEntity(entity);
                delete entity;
                m_Entities[i] = m_Entities[m_Entities.size() - 1];
                m_Entities.pop_back();
            }
        }

        m_ClearGame = false;
    }

    if (m_SaveGame)
    {
        JSON json;
        ToJSON(&json);
        std::ofstream o("save.json");
        o << std::setw(4) << json.GetJ() << std::endl;
        m_SaveGame = false;
    }

    if (m_LoadGame)
    {
        for (Entity* entity : m_Entities)
        {
            UnregisterEntity(entity);
            delete entity;
        }
        m_Entities.clear();

        std::ifstream i("save.json");
        JSON json;
        i >> json.GetJ();
        FromJSON(&json);
        FromJSONResolve(&json);

        for (Entity* entity : m_Entities)
        {
            RegisterEntity(entity);
        }

        m_LoadGame = false;
    }

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

void World::Render()
{
    for (System* system : m_RenderSystems)
    {
        system->Render(m_Window);
    }
}

Entity* World::GetEntityById(int entityId) const
{
    for (Entity* entity : m_Entities)
    {
        if (entity->GetId() == entityId)
        {
            return entity;
        }
    }
    return nullptr;
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