#include <ecs/entity.h>
#include <ecs/component.h>
#include <movement/positioncomponent.h>

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
    if (component != nullptr)
    {
        component->SetOwner(this);
        m_Components.push_back(component);
    }
}

void Entity::RemoveComponent(Component* component)
{
    if (component != nullptr)
    {
        for (int i = 0 ; i < m_Components.size() ; ++i)
        {
            if (m_Components[i] == component)
            {
                m_Components[i] = m_Components[m_Components.size() - 1];
                m_Components.pop_back();
                delete component;
                return;
            }
        }
    }
}

void Entity::ResetComponentCaches()
{
    m_PositionComponentCache.Reset();
}

PositionComponent* Entity::GetPositionComponent()
{
    return m_PositionComponentCache.GetComponent(this);
}

const PositionComponent* Entity::GetPositionComponent() const
{
    return m_PositionComponentCache.GetComponent(this);
}

ironEND_NAMESPACE