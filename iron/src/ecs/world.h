#pragma once

#include <iron.h>
#include <vector>

#pragma region usercode
#include <graphics/spritesheetmanager.h>
#pragma endregion

ironBEGIN_NAMESPACE

class JSON;
class Entity;

#pragma region usercodenamespace
class System;
class Window;
#pragma endregion

class World
{
public:
    World() {}
    const std::vector<Entity*>& GetEntities() const { return m_Entities; }

    void ToJSON(JSON* j);

private:
    std::vector<Entity*> m_Entities;

#pragma region usercodeclass
public:
    ~World();

    void CreateSystems();
    Entity* CreateEntity();
    void DestroyEntity(Entity* entity);

    void Update(float deltaTime);
    void Render(Window* window);

    SpriteSheetManager& GetSpriteSheetManager() { return m_SpriteSheetManager; }
    const SpriteSheetManager& GetSpriteSheetManager() const { return m_SpriteSheetManager; }

private:
    void RegisterEntity(Entity* entity);
    void UnregisterEntity(Entity* entity);

    std::vector<Entity*> m_PendingAddEntities;
    std::vector<Entity*> m_PendingRemoveEntities;
    std::vector<System*> m_UpdateSystems;
    std::vector<System*> m_RenderSystems;
    int m_NextEntityId = 0;
    SpriteSheetManager m_SpriteSheetManager;
#pragma endregion
};

ironEND_NAMESPACE