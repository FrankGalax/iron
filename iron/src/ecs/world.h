#pragma once

#include <iron.h>
#include <vector>
#include <graphics/spritesheetmanager.h>

ironBEGIN_NAMESPACE

class Entity;
class System;
class Window;

class World
{
public:
    ~World();

    void CreateSystems();
    Entity* CreateEntity();
    void RegisterEntity(Entity* entity);

    void Update(float deltaTime);
    void Render(Window* window);

    SpriteSheetManager& GetSpriteSheetManager() { return m_SpriteSheetManager; }
    const SpriteSheetManager& GetSpriteSheetManager() const { return m_SpriteSheetManager; }

private:
    std::vector<Entity*> m_Entities;
    std::vector<System*> m_UpdateSystems;
    std::vector<System*> m_RenderSystems;
    int m_NextEntityId = 0;
    SpriteSheetManager m_SpriteSheetManager;
};

ironEND_NAMESPACE