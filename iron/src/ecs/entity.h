#pragma once

#include <iron.h>
#include <string>
#include <vector>

#pragma region usercode
#include <ecs/componentcache.h>
#pragma endregion

ironBEGIN_NAMESPACE

class JSON;
class World;
class Component;

#pragma region usercodenamespace
class PositionComponent;
#pragma endregion

class Entity
{
public:
    Entity() {}
    Entity(int id, World* world) : m_Id(id), m_World(world) {}

    int GetId() const { return m_Id; }
    World* GetWorld() { return m_World; }
    const World* GetWorld() const { return m_World; }
    const std::string& GetName() const { return m_Name; }
    void SetName(const std::string& name) { m_Name = name; }
    const std::vector<Component*>& GetComponents() const { return m_Components; }

    void ToJSON(JSON* j);
    void FromJSON(JSON* j);

private:
    int m_Id = 0;
    World* m_World = nullptr;
    std::string m_Name;
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