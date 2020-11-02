#pragma once

#include <iron.h>
#include <vector>

ironBEGIN_NAMESPACE

class Component;
class World;

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
    void RemoveFromWorld();

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
};

ironEND_NAMESPACE