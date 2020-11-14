#pragma once

#include <iron.h>
#include <vector>
#include <string>
#include <ecs/componentcache.h>

ironBEGIN_NAMESPACE

class Component;
class World;
class PositionComponent;

class Entity
{
public:
    Entity(int id, World* world);
    ~Entity();

    int GetId() const { return m_Id; }
    const World* GetWorld() const { return m_World; }
    World* GetWorld() { return m_World; }
    void SetName(const std::string& name) { m_Name = name; }
    const std::string& GetName() const { return m_Name; }

    void AddComponent(Component* component);
    const std::vector<Component*>& GetComponents() const { return m_Components; }
    std::vector<Component*>& GetComponents() { return m_Components; }

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
    int m_Id;
    World* m_World;
    std::string m_Name = "";
    std::vector<Component*> m_Components;

    ComponentCache<PositionComponent> m_PositionComponentCache;
};

ironEND_NAMESPACE

#include <ecs/componentcacheimpl.h>