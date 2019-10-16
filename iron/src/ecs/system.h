#pragma once

#include <iron.h>
#include <vector>
#include <ecs/entity.h>

ironBEGIN_NAMESPACE

class Entity;
class Window;

#define IRON_SYSTEM_DECLARE_1(tupleClass, component1Class) \
        virtual void RegisterEntity(Entity* entity) override; \
    private: \
	    struct tupleClass \
	    { \
		    component1Class* m_##component1Class; \
	    }; \
        std::vector<tupleClass> m_Tuples; \
    public:

#define IRON_SYSTEM_DECLARE_2(tupleClass, component1Class, component2Class) \
        virtual void RegisterEntity(Entity* entity) override; \
    private: \
	    struct tupleClass \
	    { \
		    component1Class* m_##component1Class = nullptr; \
            component2Class* m_##component2Class = nullptr; \
	    }; \
        std::vector<tupleClass> m_Tuples; \
    public:

#define IRON_SYSTEM_IMPLEMENT_1(systemClass, tupleClass, component1Class) \
    void systemClass::RegisterEntity(Entity* entity) \
    { \
        component1Class* component1 = entity->GetComponent<component1Class>(); \
        if (component1 == nullptr) return; \
        tupleClass tuple; \
        tuple.m_##component1Class = component1; \
        m_Tuples.push_back(tuple); \
    } \

#define IRON_SYSTEM_IMPLEMENT_2(systemClass, tupleClass, component1Class, component2Class) \
    void systemClass::RegisterEntity(Entity* entity) \
    { \
        component1Class* component1 = entity->GetComponent<component1Class>(); \
        if (component1 == nullptr) return; \
        component2Class* component2 = entity->GetComponent<component2Class>(); \
        if (component2 == nullptr) return; \
        tupleClass tuple; \
        tuple.m_##component1Class = component1; \
        tuple.m_##component2Class = component2; \
        m_Tuples.push_back(tuple); \
    } \

class System
{
public:
    virtual void RegisterEntity(Entity* entity) = 0;

	virtual void Update(float deltaTime) {}
	virtual void Render(Window* window) {}
};

ironEND_NAMESPACE