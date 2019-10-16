#pragma once

#include <iron.h>
#include <vector>
#include <ecs/entity.h>

ironBEGIN_NAMESPACE

class Entity;
class Window;

#define IRON_SYSTEM_COMMON(tupleClass) \
	protected: \
		virtual void OnRegisterEntity(Entity* entity) override \
	{ \
		tupleClass tuple; \
		SetTuple(entity, tuple); \
		m_Tuples.push_back(tuple); \
	} \
	private: \
		std::vector<tupleClass> m_Tuples; \
	public:

#define IRON_SYSTEM_1(tupleClass, component1Class) \
	struct tupleClass \
	{ \
		component1Class* m_##component1Class; \
	}; \
	void SetTuple(Entity* entity, tupleClass& tuple) \
	{ \
		tuple.m_##component1Class = entity->GetComponent<component1Class>(); \
	} \
	virtual bool CanRegister(Entity* entity) const override \
	{ \
		if (entity->GetComponent<component1Class>() == nullptr) return false; \
		return true; \
	} \
	IRON_SYSTEM_COMMON(tupleClass)

#define IRON_SYSTEM_2(tupleClass, component1Class, component2Class) \
	struct tupleClass \
	{ \
		component1Class* m_##component1Class; \
		component2Class* m_##component2Class; \
	}; \
	void SetTuple(Entity* entity, tupleClass& tuple) \
	{ \
		tuple.m_##component1Class = entity->GetComponent<component1Class>(); \
		tuple.m_##component2Class = entity->GetComponent<component2Class>(); \
	} \
	virtual bool CanRegister(Entity* entity) const override \
	{ \
		if (entity->GetComponent<component1Class>() == nullptr) return false; \
		if (entity->GetComponent<component2Class>() == nullptr) return false; \
		return true; \
	} \
	IRON_SYSTEM_COMMON(tupleClass)

class System
{
public:
	virtual bool CanRegister(Entity* entity) const = 0;
	virtual void OnRegisterEntity(Entity* entity) = 0;
	void RegisterEntity(Entity* entity);

	virtual void Update(float deltaTime) {}
	virtual void Render(Window* window) {}
};

ironEND_NAMESPACE