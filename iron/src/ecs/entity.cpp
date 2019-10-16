#include <ecs/entity.h>
#include <ecs/component.h>

ironBEGIN_NAMESPACE

Entity::Entity(int id) :
	m_Id(id)
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
	m_Components.push_back(component);
}

ironEND_NAMESPACE