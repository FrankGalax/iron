#pragma once

#include <iron.h>
#include <vector>
#include <string>

#pragma region usercode
#include <ecs/componentcache.h>
#pragma endregion

ironBEGIN_NAMESPACE

class Component;
class World;

#pragma region usercodenamespace
class PositionComponent;
#pragma endregion

class Entity
{
public:
    Entity(int id, World* world) : m_Id(id), m_World(world) {}

    int GetId() const { return m_Id; }
    const World* GetWorld() const { return m_World; }
    World* GetWorld() { return m_World; }
    void SetName(const std::string& name) { m_Name = name; }
    const std::string& GetName() const { return m_Name; }
    const std::vector<Component*>& GetComponents() const { return m_Components; }

private:
    int m_Id;
    World* m_World;
    std::string m_Name = "";
    std::vector<Component*> m_Components;

#pragma region usercodeclass
public:
    ~Entity();

    void AddComponent(Component* component);

    void ResetComponentCaches();
    PositionComponent* GetPositionComponent();
    const PositionComponent* GetPositionComponent() const;

    template <class T>
    T* GetComponent()
    {
        for (Component* component : m_Components)
        {
            if (T* comp = dynamic_cast<T*>(component))
            {
                return comp;
            }
        }
        return nullptr;
    }

    template <class T>
    const T* GetComponent() const
    {
        for (Component* component : m_Components)
        {
            if (const T* comp = dynamic_cast<T*>(component))
            {
                return comp;
            }
        }
        return nullptr;
    }

private:
    ComponentCache<PositionComponent> m_PositionComponentCache;
#pragma endregion
};

ironEND_NAMESPACE

#pragma region usercodeend
#include <ecs/componentcacheimpl.h>
#pragma endregion