#include <ecs/entity.h>
#include <ecs/component.h>
#include <movement/positioncomponent.h>

ironBEGIN_NAMESPACE

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