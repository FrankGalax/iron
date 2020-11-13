#pragma once

#include <iron.h>

ironBEGIN_NAMESPACE

class Entity;

template<typename ComponentType>
class ComponentCache
{
public:
	void Update(const Entity* entity) const;
	ComponentType* GetComponent(const Entity* entity) const;
	void Reset();
private:
	mutable int m_Index = -1;
};

ironEND_NAMESPACE