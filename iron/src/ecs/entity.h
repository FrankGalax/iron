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
	void AddComponent(Component* component);

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

	const World* GetWorld() const { return m_World; }

private:
	int m_Id;
	World* m_World;
	std::vector<Component*> m_Components;
};

ironEND_NAMESPACE