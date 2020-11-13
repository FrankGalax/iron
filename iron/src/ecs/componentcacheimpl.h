#pragma once

#include <iron.h>
#include <assert.h>

ironBEGIN_NAMESPACE

template<typename ComponentType>
ComponentType* ComponentCache<ComponentType>::GetComponent(const Entity* entity) const
{
	if (m_Index == -1)
	{
		Update(entity);
	}

	if (m_Index != -1)
	{
		assert(m_Index < entity->GetComponents().size());

		Component* component = *(entity->GetComponents().begin() + m_Index);

		return static_cast<ComponentType*> (component);
	}

	return nullptr;
}

template<typename ComponentType>
void ComponentCache<ComponentType>::Update(const Entity* entity) const
{
	m_Index = -1;

	for (int i = 0; i < entity->GetComponents().size(); ++i)
	{
		if (dynamic_cast<ComponentType*>(entity->GetComponents()[i]) != nullptr)
		{
			m_Index = i;
			return;
		}
	}
}

template<typename ComponentType>
inline void ComponentCache<ComponentType>::Reset()
{
    m_Index = -1;
}

ironEND_NAMESPACE