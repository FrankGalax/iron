#pragma once

#include <iron.h>
#include <vector>
#include <ecs/entity.h>

ironBEGIN_NAMESPACE

class Entity;
class Window;

#define IRON_SYSTEM_DECLARE_1(tupleClass, component1Class) \
    virtual void RegisterEntity(Entity* entity) override; \
    virtual void UnregisterEntity(Entity* entity) override; \
    private: \
        struct tupleClass \
        { \
            Entity* m_Entity = nullptr; \
            component1Class* m_##component1Class = nullptr; \
        }; \
        std::vector<tupleClass> m_Tuples; \
    public:

#define IRON_SYSTEM_DECLARE_2(tupleClass, component1Class, component2Class) \
    virtual void RegisterEntity(Entity* entity) override; \
    virtual void UnregisterEntity(Entity* entity) override; \
    private: \
        struct tupleClass \
        { \
            Entity* m_Entity = nullptr; \
            component1Class* m_##component1Class = nullptr; \
            component2Class* m_##component2Class = nullptr; \
        }; \
        std::vector<tupleClass> m_Tuples; \
    public:
    
#define IRON_SYSTEM_DECLARE_3(tupleClass, component1Class, component2Class, component3Class) \
    virtual void RegisterEntity(Entity* entity) override; \
    virtual void UnregisterEntity(Entity* entity) override; \
    private: \
        struct tupleClass \
        { \
            Entity* m_Entity = nullptr; \
            component1Class* m_##component1Class = nullptr; \
            component2Class* m_##component2Class = nullptr; \
            component3Class* m_##component3Class = nullptr; \
        }; \
        std::vector<tupleClass> m_Tuples; \
    public:

#define IRON_SYSTEM_DECLARE_4(tupleClass, component1Class, component2Class, component3Class, component4Class) \
    virtual void RegisterEntity(Entity* entity) override; \
    virtual void UnregisterEntity(Entity* entity) override; \
    private: \
        struct tupleClass \
        { \
            Entity* m_Entity = nullptr; \
            component1Class* m_##component1Class = nullptr; \
            component2Class* m_##component2Class = nullptr; \
            component3Class* m_##component3Class = nullptr; \
            component4Class* m_##component4Class = nullptr; \
        }; \
        std::vector<tupleClass> m_Tuples; \
    public:

#define IRON_SYSTEM_DECLARE_5(tupleClass, component1Class, component2Class, component3Class, component4Class, component5Class) \
    virtual void RegisterEntity(Entity* entity) override; \
    virtual void UnregisterEntity(Entity* entity) override; \
    private: \
        struct tupleClass \
        { \
            Entity* m_Entity = nullptr; \
            component1Class* m_##component1Class = nullptr; \
            component2Class* m_##component2Class = nullptr; \
            component3Class* m_##component3Class = nullptr; \
            component4Class* m_##component4Class = nullptr; \
            component5Class* m_##component5Class = nullptr; \
        }; \
        std::vector<tupleClass> m_Tuples; \
    public:

#define IRON_SYSTEM_IMPLEMENT_COMMON(systemClass, tupleClass) \
    void systemClass::UnregisterEntity(Entity* entity) \
    { \
        for (int i = 0 ; i < m_Tuples.size() ; ++i) \
        { \
            if (m_Tuples[i].m_Entity == entity) \
            { \
                size_t lastIndex = m_Tuples.size() - 1; \
                m_Tuples[i] = m_Tuples[lastIndex]; \
                m_Tuples[lastIndex] = m_Tuples[i]; \
                m_Tuples.pop_back(); \
                return; \
            } \
        } \
    }
#define IRON_SYSTEM_IMPLEMENT_1(systemClass, tupleClass, component1Class) \
    void systemClass::RegisterEntity(Entity* entity) \
    { \
        component1Class* component1 = entity->GetComponent<component1Class>(); \
        if (component1 == nullptr) return; \
        tupleClass tuple; \
        tuple.m_Entity = entity; \
        tuple.m_##component1Class = component1; \
        m_Tuples.push_back(tuple); \
        OnRegisterEntity(); \
    } \
    IRON_SYSTEM_IMPLEMENT_COMMON(systemClass, tupleClass)

#define IRON_SYSTEM_IMPLEMENT_2(systemClass, tupleClass, component1Class, component2Class) \
    void systemClass::RegisterEntity(Entity* entity) \
    { \
        component1Class* component1 = entity->GetComponent<component1Class>(); \
        if (component1 == nullptr) return; \
        component2Class* component2 = entity->GetComponent<component2Class>(); \
        if (component2 == nullptr) return; \
        tupleClass tuple; \
        tuple.m_Entity = entity; \
        tuple.m_##component1Class = component1; \
        tuple.m_##component2Class = component2; \
        m_Tuples.push_back(tuple); \
        OnRegisterEntity(); \
    } \
    IRON_SYSTEM_IMPLEMENT_COMMON(systemClass, tupleClass)

#define IRON_SYSTEM_IMPLEMENT_2_1(systemClass, tupleClass, component1Class, component2Class, component3Class) \
    void systemClass::RegisterEntity(Entity* entity) \
    { \
        component1Class* component1 = entity->GetComponent<component1Class>(); \
        if (component1 == nullptr) return; \
        component2Class* component2 = entity->GetComponent<component2Class>(); \
        if (component2 == nullptr) return; \
        component3Class* component3 = entity->GetComponent<component3Class>(); \
        tupleClass tuple; \
        tuple.m_Entity = entity; \
        tuple.m_##component1Class = component1; \
        tuple.m_##component2Class = component2; \
        tuple.m_##component3Class = component3; \
        m_Tuples.push_back(tuple); \
        OnRegisterEntity(); \
    } \
    IRON_SYSTEM_IMPLEMENT_COMMON(systemClass, tupleClass)

#define IRON_SYSTEM_IMPLEMENT_2_2(systemClass, tupleClass, component1Class, component2Class, component3Class, component4Class) \
    void systemClass::RegisterEntity(Entity* entity) \
    { \
        component1Class* component1 = entity->GetComponent<component1Class>(); \
        if (component1 == nullptr) return; \
        component2Class* component2 = entity->GetComponent<component2Class>(); \
        if (component2 == nullptr) return; \
        component3Class* component3 = entity->GetComponent<component3Class>(); \
        component4Class* component4 = entity->GetComponent<component4Class>(); \
        tupleClass tuple; \
        tuple.m_Entity = entity; \
        tuple.m_##component1Class = component1; \
        tuple.m_##component2Class = component2; \
        tuple.m_##component3Class = component3; \
        tuple.m_##component4Class = component4; \
        m_Tuples.push_back(tuple); \
        OnRegisterEntity(); \
    } \
    IRON_SYSTEM_IMPLEMENT_COMMON(systemClass, tupleClass)

#define IRON_SYSTEM_IMPLEMENT_2_3(systemClass, tupleClass, component1Class, component2Class, component3Class, component4Class, component5Class) \
    void systemClass::RegisterEntity(Entity* entity) \
    { \
        component1Class* component1 = entity->GetComponent<component1Class>(); \
        if (component1 == nullptr) return; \
        component2Class* component2 = entity->GetComponent<component2Class>(); \
        if (component2 == nullptr) return; \
        component3Class* component3 = entity->GetComponent<component3Class>(); \
        component4Class* component4 = entity->GetComponent<component4Class>(); \
        component5Class* component5 = entity->GetComponent<component5Class>(); \
        tupleClass tuple; \
        tuple.m_Entity = entity; \
        tuple.m_##component1Class = component1; \
        tuple.m_##component2Class = component2; \
        tuple.m_##component3Class = component3; \
        tuple.m_##component4Class = component4; \
        tuple.m_##component5Class = component5; \
        m_Tuples.push_back(tuple); \
        OnRegisterEntity(); \
    } \
    IRON_SYSTEM_IMPLEMENT_COMMON(systemClass, tupleClass)

class System
{
public:
    virtual void RegisterEntity(Entity* entity) = 0;
    virtual void UnregisterEntity(Entity* entity) = 0;

    virtual void Update(float deltaTime) {}
    virtual void Render(Window* window) {}
protected:
    virtual void OnRegisterEntity() {}
};

ironEND_NAMESPACE