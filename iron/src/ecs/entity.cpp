#include <ecs/entity.h>
#include <ecs/component.h>

ironBEGIN_NAMESPACE

Entity::Entity(int id, World* world) :
    m_Id(id), m_World(world)
{
}

Entity::~Entity()
{
    for (Component* component : m_Components)
    {
        delete component;
    }
}

void Entity::AddComponent(Component* component)
{
    component->SetOwner(this);
    m_Components.push_back(component);
}

void Entity::RemoveFromWorld()
{
    m_World = nullptr;
}

ironEND_NAMESPACE